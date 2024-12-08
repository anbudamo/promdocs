Follow these instructions to setup both the nodes.
**node0:**

1. Install Prometheus:
sudo apt update && upgrade
sudo apt install prometheus

2. Create the config file: sudo nano /etc/prometheus/prometheus.yml

3. Add the master.yml code in promdocs repo to prometheus.yml:
can also refer to: https://stackoverflow.com/questions/70094753/prometheus-monitoring-for-remote-network 

4. Create the following script.sh to add the necessary flags on startup:
/usr/local/bin/prometheus \
 --config.file /etc/prometheus/prometheus.yml \
 --storage.tsdb.path /var/lib/prometheus/ \
 --web.console.templates=/etc/prometheus/consoles \
 --web.console.libraries=/etc/prometheus/console_libraries \
 --web.enable-remote-write-receiver

5. Start Prometheus: sudo bash script.sh 

**node1:**

1. Install Prometheus:
sudo apt update && upgrade
sudo apt install prometheus

2. Create the config file: sudo nano /etc/prometheus/prometheus.yml

3. Add the job.yml code in promdocs repo to prometheus.yml:

4. Download the c-api client:
curl -L -o prometheus-client-c-v0.1.3.tar.gz https://github.com/digitalocean/prometheus-client-c/archive/refs/tags/v0.1.3.tar.gz
tar -xzf prometheus-client-c-v0.1.3.tar.gz
cd prometheus-client-c-0.1.3
sudo apt install cmake
- cd to prom
  mkdir build
  cmake --install-prefix=/usr/local ..
  sudo make install
  export LD_LIBRARY_PATH=/usr/local/lib:$LD_LIBRARY_PATH
- cd to promhttp
  sudo apt-get install libmicrohttpd-dev
  mkdir build
  cmake --install-prefix=/usr/local .
  sudo make install
  * you will get this error "note: expected ‘MHD_AccessHandlerCallback’ "
  open the CMakeLists.txt in promhttp and remove the -werror flag in all the 'target_compile_options'
  sudo make install

5. cd back to your root directory, create new driver file called main.c, and copy the promdocs/main.c code to it

6. Start Prometheus:
sudo systemctl prometheus enable 
sudo systemctl prometheus start

7. 
