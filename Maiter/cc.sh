##########################
# Do not change it!!! CC use pagerank Iterate Kernel
ALGORITHM=Pagerank
###########################

WORKERS=4
GRAPH=/home/ubuntu/chengyangliu/maiter/Maiter/data/vldb2014
RESULT=/home/ubuntu/chengyangliu/maiter/Maiter/data/output
NODES=13
SNAPSHOT=1
TERMTHRESH=0.1
BUFMSG=500
PORTION=0.2


./bin/release/examples/example-dsm  --runner=$ALGORITHM --workers=$WORKERS --graph_dir=$GRAPH --result_dir=$RESULT --num_nodes=$NODES --snapshot_interval=$SNAPSHOT --portion=$PORTION --termcheck_threshold=$TERMTHRESH --bufmsg=$BUFMSG --v=0 > static.log
