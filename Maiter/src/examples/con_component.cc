#include "client/client.h"


using namespace dsm;

//DECLARE_string(graph_dir);
DECLARE_string(result_dir);
DECLARE_int64(num_nodes);
DECLARE_double(portion);

struct PagerankIterateKernel : public IterateKernel<int, int, vector<int> > {
    int zero;


    PagerankIterateKernel() : zero(0){}
   
    // CC input format: vid  neighbors'number  nid1  elabel1  ndi2  elabel2  ...
    // seperated with "\t"
    // IF INPUT DATA ARE OTHER FORMAT, YOU CAN MODIFY THIS FUNCTION TO FIT IT.
    void read_data(string& line, int& k, vector<int>& data){
        char *c_line = (char*)line.c_str();
        char *pch;
        pch=strtok(c_line, "\t");
        int source = atoi(pch);

        pch=strtok(NULL, "\t");
        int num = atoi(pch);
        if (num == 0) return;

        vector<int> linkvec;
        for(int i=0; i<num; i++) {
            pch=strtok(NULL, "\t");
            linkvec.push_back(atoi(pch));
            pch=strtok(NULL, "\t"); //filter elabel
        }

        k = source;
        //std::cout << "source:" << k << std::endl;
        data = linkvec;
    }

    void init_c(const int& k, int& delta, vector<int>& data){
            int  init_delta = k;
            delta = init_delta;
    }

    void init_v(const int& k,int& v,vector<int>& data){
            v=0;
    }
    void accumulate(int& a, const int& b){
            a=std::max(a,b);
    }

    void priority(int& pri, const int& value, const int& delta){
            pri = value-std::max(value,delta);
    }

    void g_func(const int& k,const int& delta, const int& value, const vector<int>& data, vector<pair<int, int> >* output){
            int outv = value;
            
            //cout << "size " << size << endl;
            for(vector<int>::const_iterator it=data.begin(); it!=data.end(); it++){
                    int target = *it;
                    output->push_back(make_pair(target, outv));
            }
    }

    const int& default_v() const {
        return zero;
    }
};


static int Pagerank(ConfigData& conf) {
    MaiterKernel<int, int, vector<int> >* kernel = new MaiterKernel<int, int, vector<int> >(
                                        conf, FLAGS_num_nodes, FLAGS_portion, FLAGS_result_dir,
                                        new Sharding::Mod,
                                        new PagerankIterateKernel,
                                        new TermCheckers<int, int>::Diff);
    
    
    kernel->registerMaiter();

    if (!StartWorker(conf)) {
        Master m(conf);
        m.run_maiter(kernel);
    }
    
    delete kernel;
    return 0;
}

REGISTER_RUNNER(Pagerank);

