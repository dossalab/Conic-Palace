#!/usr/bin/env sh

#
# Part of the Conic Palace - robot control center
#
# Runs build in docker container. Useful for cross-compiling
# app to windows or building without native go toolchain
#
# See LICENSE.md for licensing information
# Roman Luitko, 2020
#

IMAGE_TAG=conic_palace_docker_image
LOGNAME=$(logname)
MINGW_ROOT="/usr/x86_64-w64-mingw32/sys-root/mingw"

info() {
	printf "[info]\t%s\n" "$1"
}

print_usage() {
	info "usage $0 [target: windows | linux ] outdir"
	exit 1
}

check_image_exists() {
	docker image inspect $1 >/dev/null 2>&1
}

build() {
	if ! check_image_exists $IMAGE_TAG; then
		info "image $IMAGE_TAG is not exist, creating..."
		docker build -t $IMAGE_TAG build/package
	fi

	info "using username '$LOGNAME' to obtain uid and gid..."

	case $1 in
	windows)
		info "building windows app..."
		# oh god, oh fuck
		docker run \
			--mount "type=bind,src=$(pwd),dst=/tmp/build" \
			--env "PKG_CONFIG_PATH=$MINGW_ROOT/lib/pkgconfig" \
			--env "CGO_ENABLED=1" \
			--env "CGO_LDFLAGS_ALLOW=-Wl,-luuid" \
			--env "CC=x86_64-w64-mingw32-gcc" \
			--env "GOOS=windows" \
			--env "GOARCH=amd64" \
			--env "GOCACHE=/tmp/build/.cache/go-build" \
			--env "MINGW_BUNDLEDLLS_SEARCH_PATH=$MINGW_ROOT/bin" \
			--workdir /tmp/build \
			--user "$(id -u $LOGNAME):$(id -g $LOGNAME)" $IMAGE_TAG \
			/bin/sh -c "go build -o $2 -ldflags -H=windowsgui && \
			./third_party/mingw-bundledlls --copy $2 && \
			./scripts/nsisgen.py \
				--name 'Conic Palace' \
				--exe '`basename $2`' \
				--dir '`dirname $2`' \
				--author 'Conic Software Authors' \
				--outfile '`dirname $2`/../installer.exe'"
		;;
	linux)
		info "building linux app is not supported for now"
		;;
	*)
		print_usage
		;;
	esac
}

[ $# -ne 2 ] && print_usage
[ $(id -u) -ne 0 ] && info "please, execute as root!" && exit 1
build $1 $2

