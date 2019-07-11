ALGORITHM=Pagerank
WORKERS=2
GRAPH=input/pagerank
RESULT=result/pagerank
NODES=1000000
SNAPSHOT=1
TERMTHRESH=0.0001
BUFMSG=500
PORTION=0.1

./maiter  --runner=$ALGORITHM --workers=$WORKERS --graph_dir=$GRAPH --result_dir=$RESULT --num_nodes=$NODES --snapshot_interval=$SNAPSHOT --portion=$PORTION --termcheck_threshold=$TERMTHRESH --bufmsg=$BUFMSG --v=0 > log
