**node0:**

script.sh:
/usr/local/bin/prometheus \
 --config.file /etc/prometheus/prometheus.yml \
 --storage.tsdb.path /var/lib/prometheus/ \
 --web.console.templates=/etc/prometheus/consoles \
 --web.console.libraries=/etc/prometheus/console_libraries \
 --web.enable-remote-write-receiver

run using sudo bash script.sh 

.yml:
global:
  scrape_interval: 15s
  evaluation_interval: 15s

scrape_configs:
  - job_name: 'prometheus'
    static_configs:
      - targets: ['localhost:9090']

refer to: https://stackoverflow.com/questions/70094753/prometheus-monitoring-for-remote-network 

**node1:**

.yml: 
global:
  scrape_interval:     15s # Set the scrape interval to every 15 seconds. Default is every 1 minute.
  evaluation_interval: 15s # Evaluate rules every 15 seconds. The default is every 1 minute.

remote_write:
  - url: http://10.10.1.1:9090/api/v1/write

scrape_configs:
  - job_name: local1
    scrape_interval: 5s
    static_configs:
      - targets: ['localhost:8000']
