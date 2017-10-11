#!/bin/sh -x


IROHA_HOME=$(dirname $(realpath $0))/..
MOUNT=/tmp/iroha
BUILD_PATH=/tmp/build
PROJ_BIN=/opt/iroha

# You can either pull image or build your own (this is only base for iroha)
# docker pull hyperledger/iroha-docker-develop
docker build $IROHA_HOME/docker/develop -t hyperledger/iroha-docker

# The actual build
docker run -tdv $IROHA_HOME:$MOUNT hyperledger/iroha-docker sh <<EOF
mkdir -p $BUILD_PATH $PROJ_BIN;
cd $BUILD_PATH && cmake -DTESTING=OFF $MOUNT && make;
cp $BUILD_PATH/bin/* $PROJ_BIN;
ldd $PROJ_BIN/* | egrep '(ed25519|gflags|boost)' | sort | uniq | egrep -o '\/.*?\.(so(\..*?)?|a)\s' | xargs cp -t /usr/lib;
ldd $PROJ_BIN/* | grep stdc++ | head -n 1 | egrep -o '\/.*?\.(so(\..*?)?|a)\s' | xargs cp -t /usr/lib/x86_64-linux-gnu/
EOF

docker commit $CONTAINER hyperledger/iroha-docker
docker stop $CONTAINER && docker rm $CONTAINER
docker save -o "$IROHA_HOME"/build/iroha-dev.tar hyperledger/iroha-docker
