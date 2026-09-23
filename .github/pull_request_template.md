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

### Protected US verification (maintainer approval)

Once activated, the maintainer dispatches the private verifier for every PR against
the exact PR head and base. **US ROM verification (maintainer approved)** must
pass on the current merge revision before merging once the gate is activated.
New commits or base changes require another run. Tooling/layout/reference changes
require review and promotion of the verifier's pinned tooling first.
See [CI setup and review](docs/ci.md). Do not attach ROMs, objects, raw assembly,
or private build logs to the PR.

### Contributor's local evidence

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
