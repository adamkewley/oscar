# `docker/` Linux-Based Development Environments

## Cheatsheet

```bash
# List all images
docker images

# Delete `fooimage`
docker rmi fooimage

# List all containers
docker ps

# Prune all not-running containers
docker container prune

# Build a development environment image
cd docker && docker build -t oscar-ubuntu22 -f ubuntu22-ci.Dockerfile . && cd -

# Build project via the environment
docker run --rm -v "${PWD}:/project" -w /project oscar-ubuntu22 ./scripts/e2e_build_ubuntu22.sh Development
```
