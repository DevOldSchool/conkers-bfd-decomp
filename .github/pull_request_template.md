## Summary

Describe the function, tooling, or documentation change.

## Verification

### Public checks (automatic; no ROM access)

- Repository metadata
- Generated progress consistency
- PR whitespace and prohibited files
- Python tests and shell syntax
- Toolchain image and compiler smoke test
- US C compilation (no ROM; not match evidence)
- GitHub workflow syntax
- All public PR checks passed (required aggregate after ruleset migration)

### Local US verification before merge

A contributor or maintainer with the US ROM performs the checks below and records
the tested commit and results. Contributors without a ROM may ask a maintainer
to verify their PR. GitHub does not enforce this local ROM evidence; the existing
approved-main ROM workflow runs after merge. See [CI and review](docs/ci.md).
Do not attach ROMs, objects, generated assembly or private build logs.

Tested commit:

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
