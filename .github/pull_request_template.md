## Summary

Describe the function, tooling, or documentation change.

## Verification

For function work, include exact output for the active US target:

```text
./conker diff <work-item-id>
./conker progress match <work-item-id>
# Only after reviewed boundary evidence and every source-unit member matches:
./conker progress integrate <work-item-id>
./conker progress check
git -c core.whitespace=cr-at-eol diff --check
```

For a logical function batch, also report the test suite once. For game-overlay
or shared build changes, report one clean `./conker game-build --refresh` result;
these batch checks are not required after each small function.

State whether the diff reports `CURRENT (0)`. If this is tooling-only work,
describe the relevant test command instead.

## Checklist

- [ ] This change does not add ROMs, extracted assets, generated assembly, or build output.
- [ ] I did not copy C sources, symbols, comments, or generated material from another decompilation project.
- [ ] The linked issue is claimed by me or this work was approved by a maintainer.
