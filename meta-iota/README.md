# Iota OS

This is meta layer dedicated to support Arm fast models.

# Iota setup

The way to start the setup to build the distribution is to fetch the
iota-manifest. For that, first install repo tool from google:

```
curl http://commondatastorage.googleapis.com/git-repo-downloads/repo > /tmp/repo
sudo install -m 0755 /tmp/repo /usr/local/bin/repo;
```

and then fetch the manifest:
```
mkdir ~/iota; cd ~/iota
repo init -u oteutoehuote -b master -m default.xml
repo sync
```

after setup the following environment variables to set the distribution and the
machine type of the build, for now only vexpress-a32 is totally tested, but
others will follow:

```
export DISTRO="iota"
export MACHINE="vexpress-a32"
```

Then prepare the environment to run the build, in the top directory

```
source setup-environment
```

This will create and put you ready to start the build in a topdir/build-iota
directory, to start the build just type:

```
bitbake iota-tiny-image
```

The first build is long and can take several minutes to conclude, when finished
check the resulted binaries in the deploy directory

```
 ~/iota/build-iota/tmp-iota/deploy/images/vexpress-a32/
```

To load the resulted flash img in the FVP model

```
YOCTO_OUTDIR=~/iota/build-iota/tmp-iota/deploy/images/vexpress-a32

./host/FVP_Base_Cortex-A32x1 \
	-C bp.secureflashloader.fname=${YOCTO_OUTDIR}/bl1.bin \
	-C bp.flashloader0.fname=${YOCTO_OUTDIR}/iota-tiny-image-vexpress-a32.wic

```
