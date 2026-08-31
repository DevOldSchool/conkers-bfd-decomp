# Continuous integration

Public pull-request checks never download or handle a game ROM. They validate
project metadata, generated progress, shell syntax, unit tests, whitespace, and
the public Docker image build. The image check also compiles
`tests/fixtures/ido_smoke.c`, so a present-but-broken IDO installation fails CI.

`rom-verify-main.yml` runs only against protected `main`, including when it is
manually dispatched. It always checks out `main`, never a pull-request ref. It
retrieves `baserom.us.z64` from the private `DevOldSchool/conkers-bfd-assets`
repository with the environment-scoped `ROM_ASSETS_READ_TOKEN`, then runs
`./conker build --all`. The future EU/PAL ROM is not exposed to or required by
the active verification job.

Configure the `rom-verification` GitHub environment so that only maintainers
can use its secret. Do not add ROM secrets to public PR workflows or use
`pull_request_target` to validate forks.

Local toolchain commands default to the exact container digest recorded in
`toolchain/tools.lock.json`. Runtime containers have networking disabled, use a
read-only root filesystem, drop Linux capabilities, and do not mount Git
metadata or local setup. Source and ROM inputs are read-only; only generated
output directories are normally writable. Integration and libultra commands
receive their explicitly required additional writable directories.
`CONKER_IMAGE` remains an explicit override for locally built CI images. Docker
builds use an allowlisted context containing only the Dockerfile and its Python
constraint input.
