#!/bin/bash

#
# This simple script starts redis and postgres docker containers,
# and installs environment variables of the caller. Can be safely
# executed as many times as needed (it performs autocleaning).
#
# Usage:
# source local-develop.sh
#

function dependency(){
	(command -v $1 > /dev/null || (echo "install $1" && exit 1))
}

dependency jq     || exit 1
dependency docker || exit 2
dependency grep   || exit 3
dependency sed    || exit 4

# cleanup
docker rm -f pg rd 2>/dev/null 1>&2

# vars
user=postgres
password=mysecretpassword
pgport=5432
rdport=6379

# run postgres and redis
pgid=$(docker run -p 127.0.0.1:$pgport:$pgport --rm --name pg -e POSTGRES_USER=$user -e POSTGRES_PASSSWORD=$password -d postgres:9.5)
rdid=$(docker run -p 127.0.0.1:$rdport:$rdport --rm --name rd -d redis:3.2.8)

pgip=$(docker inspect $pgid | jq .[0].NetworkSettings.IPAddress | sed "s/\"//g")
rdip=$(docker inspect $rdid | jq .[0].NetworkSettings.IPAddress | sed "s/\"//g")

# stderr
>&2 echo "postgres: $pgip:$pgport {login: $user, pwd: $password}"
>&2 echo "redis:    $rdip:$rdport"

# print variables (stdout)
cat << EOF
export IROHA_POSTGRES_HOST=$pgip
export IROHA_POSTGRES_PORT=$pgport
export IROHA_POSTGRES_USER=$user
export IROHA_POSTGRES_DATABASE=$user
export IROHA_POSTGRES_PASSWORD=$password
export IROHA_REDIS_HOST=$rdip
export IROHA_REDIS_PORT=$rdport
EOF

# apply variables
export IROHA_POSTGRES_HOST=$pgip
export IROHA_POSTGRES_PORT=$pgport
export IROHA_POSTGRES_USER=$user
export IROHA_POSTGRES_DATABASE=$user
export IROHA_POSTGRES_PASSWORD=$password
export IROHA_REDIS_HOST=$rdip
export IROHA_REDIS_PORT=$rdport
