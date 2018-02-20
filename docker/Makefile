.PHONY: help

help: ## This help.
	@awk 'BEGIN {FS = ":.*?## "} /^[0-9a-zA-Z_-]+:.*?## / {printf "\033[36m%-40s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

.DEFAULT_GOAL := help

# DOCKER TASKS
xenial-cpp-tdd-book-updated-libs: ## Build Custom Xenial Enviroment for C++ TDD | (non NVIDIA)
	./build.sh generic-card codookie/xenial:cpp-tdd-book-updated-libs
	@printf "\n\033[92mDocker Image: codookie/xenial:cpp-tdd-book-updated-libs\033[0m\n"
xenial-cpp-tdd-book-updated-libs-nvidia: xenial-cpp-tdd-book-updated-libs ## Build Custom Xenial Enviroment for C++ TDD | (for NVIDIA & OpenGL)
	./build.sh nvidia-opengl codookie/xenial:cpp-tdd-book-updated-libs-nvidia
	@printf "\n\033[92mDocker Image: codookie/xenial:cpp-tdd-book-updated-libs-nvidia\033[0m\n"