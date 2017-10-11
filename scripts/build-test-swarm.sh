#!/bin/sh -x

if [ -z "$1" ] || [ "$1" -le "0" ]; then
    echo "Usage: $0 <number_of_peers>"
    exit -1
fi
LAST_PEER_ID=$(($1-1))

if ! docker-machine >/dev/null 2>&1; then
    echo "docker-machine not found"
    exit 3
fi

IROHA_HOME=$(dirname $0)/../
IMAGE="$IROHA_HOME/build/iroha-dev.tar"
PREFIX=peer

# Create nodes
for i in $(seq 0 $LAST_PEER_ID); do
    docker-machine create "$PREFIX$i";
done

# Manager node
IP=$(docker-machine inspect ${PREFIX}0 | grep IPAddress | egrep -o "[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}.[0-9]{1,3}")
eval $(docker-machine env "${PREFIX}0")
INVITE=$(docker swarm init --advertise-addr=$IP | egrep -o 'docker\sswarm\sjoin\s.*$')

# Join to the swarm by the rest
for i in $(seq 1 $LAST_PEER_ID); do
    eval $(docker-machine env "$PREFIX$i")
    eval $INVITE

    # only for tests
    docker-machine ssh "${PREFIX}0" node promote "$PREFIX$i";
done

# Load local image if possible
if [ -f "$IMAGE" ]; then
    for i in $(seq 0 $LAST_PEER_ID); do
        eval $(docker-machine env "$PREFIX$i")
        docker load -i $IMAGE;
    done
fi

eval $(docker-machine env -u)

