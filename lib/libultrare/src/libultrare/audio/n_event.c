#include "n_audio_partial.h"
#include "n_audio_list.h"

/* Complete US 0x1C060:0x1C690. Conker inlines the SDK list operations,
 * uses flag bits for interrupt masking and the final free slot, and returns
 * the first removed event time from flush. Runtime event size remains 0x10.
 */
void n_alEvtqNew(ALEventQueue *evtq, ALEventListItem *items, s32 itemCount)
{
	s32 i;

	evtq->eventCount     = 0;
	evtq->allocList.next = 0;
	evtq->allocList.prev = 0;
	evtq->freeList.next  = 0;
	evtq->freeList.prev  = 0;

	for (i = 0; i < itemCount; i++) {
		CONKER_AUDIO_LINK((ALLink *)&items[i], &evtq->freeList);
	}
}

ALMicroTime n_alEvtqNextEvent(ALEventQueue *evtq, ALEvent *evt)
{
	ALEventListItem *item;
	ALMicroTime delta;


	item = (ALEventListItem *)evtq->allocList.next;

	if (item) {
		CONKER_AUDIO_UNLINK((ALLink *)item);
		bcopy(&item->evt, evt, sizeof(*evt));
		CONKER_AUDIO_LINK((ALLink *)item, &evtq->freeList);
		delta = item->delta;
	} else {
		/* sct 11/28/95 - If we get here, most like we overflowed the event queue */
		/* with non-self-perpetuating events.  Eg. if we filled the evtq with volume */
		/* events, then when the seqp is told to play it will handle all the events */
		/* at once completely emptying out the queue.  At this point this problem */
		/* must be treated as an out of resource error and the evtq should be increased. */
		evt->type = -1;
		delta = 0;
	}


	return delta;
}

void n_alEvtqPostEvent(ALEventQueue *evtq, ALEvent *evt, ALMicroTime delta, s32 flags)
{
	ALEventListItem *item;
	ALEventListItem *nextItem;
	ALLink *node;
	s32 postAtEnd = 0;
	OSIntMask mask;

	if (flags & 2) {
		mask = osSetIntMask(OS_IM_NONE);
	}

	item = (ALEventListItem *)evtq->freeList.next;

	if (!item) {
		if (flags & 2) {
			osSetIntMask(mask);
		}
		return;
	}

	if (!item->node.next && !(flags & 1)) {
		if (flags & 2) {
			osSetIntMask(mask);
		}
		return;
	}

	CONKER_AUDIO_UNLINK((ALLink *)item);
	bcopy(evt, &item->evt, sizeof(*evt));

	if (delta == AL_EVTQ_END) {
		postAtEnd = -1;
	}

	for (node = &evtq->allocList; node != 0; node = node->next) {
		if (!node->next) { /* end of the list */
			if (postAtEnd) {
				item->delta = 0;
			} else {
				item->delta = delta;
			}

			CONKER_AUDIO_LINK((ALLink *)item, node);
			break;
		} else {
			nextItem = (ALEventListItem *)node->next;

			if (delta < nextItem->delta) {
				item->delta = delta;
				nextItem->delta -= delta;

				CONKER_AUDIO_LINK((ALLink *)item, node);
				break;
			}

			delta -= nextItem->delta;
		}
	}

	if (flags & 2) {
		osSetIntMask(mask);
	}
}

ALMicroTime n_alEvtqFlushType(ALEventQueue *evtq, s16 type)
{
	ALLink *thisNode;
	ALLink *nextNode;
	ALEventListItem *thisItem, *nextItem;
	OSIntMask mask;
	ALMicroTime firstDelta = 0;
	ALMicroTime totalDelta = 0;

	mask = osSetIntMask(OS_IM_NONE);

	thisNode = evtq->allocList.next;

	while (thisNode != 0) {
		nextNode = thisNode->next;
		thisItem = (ALEventListItem *)thisNode;
		nextItem = (ALEventListItem *)nextNode;

		totalDelta += thisItem->delta;
		if (thisItem->evt.type == type) {
			if (!firstDelta) {
				firstDelta = totalDelta;
			}
			if (nextItem) {
				nextItem->delta += thisItem->delta;
			}

			CONKER_AUDIO_UNLINK(thisNode);
			CONKER_AUDIO_LINK(thisNode, &evtq->freeList);
		}

		thisNode = nextNode;
	}

	osSetIntMask(mask);
	return firstDelta;
}
