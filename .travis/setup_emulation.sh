#!/usr/bin/env bash

docker_daemon_conf_file=/etc/docker/daemon.json

set -ex
echo "docker status:"
#systemctl status docker
echo "initial docker daemon config should be: `sudo cat $docker_daemon_conf_file || true`"
sudo ls -l $docker_daemon_conf_file
docker version -f '{{.Server.Experimental}}'

#echo '{"experimental": true}' | sudo tee -a /etc/docker/daemon.json > /dev/null
sudo cat $docker_daemon_conf_file | jq '. + {"experimental": true}' | sudo tee $docker_daemon_conf_file > /dev/null
echo "docker daemon config should be: `sudo cat $docker_daemon_conf_file || true`"
sudo ls -l $docker_daemon_conf_file

echo 'restarting docker'
sudo service docker restart
systemctl status docker
docker version -f '{{.Server.Experimental}}'
echo "docker daemon config should be: `sudo cat $docker_daemon_conf_file || true`"

#sudo systemctl restart docker
#systemctl status docker

echo 'checking for docker experimental...'
docker version -f '{{.Server.Experimental}}'

sudo docker run --rm --privileged multiarch/qemu-user-static:register --reset
set +ex
