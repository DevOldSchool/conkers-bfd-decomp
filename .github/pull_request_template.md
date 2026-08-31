## Summary

Describe the function, tooling, or documentation change.

## Verification

For function work, include exact output for the active US target:

```text
./conker finish <work-item-id>
# Only after reviewed boundary evidence and every source-unit member matches:
./conker progress integrate <work-item-id>
# If integration ran after finish:
./conker progress check && git -c core.whitespace=cr-at-eol diff --check
```

After the final function in a logical batch, report one successful
`./conker verify-batch <work-item-id> [<work-item-id>...]` result. It performs
the required overlay builds, test suite, metadata, generated-progress, and
whitespace checks; these batch checks are not required after each small
function.

State whether the diff reports `CURRENT (0)`. If this is tooling-only work,
describe the relevant test command instead.

## Checklist

- [ ] This change does not add ROMs, extracted assets, generated assembly, or build output.
- [ ] I did not copy C sources, symbols, comments, or generated material from another decompilation project.
- [ ] Any issue recorded for this work item is claimed by me, or no issue is recorded.
