#include <bits/stdc++.h>
#include<omp.h>

using namespace std;

void count_word(vector<string>content, vector<string> keywords, int num_t)
{
    int count = 0;
    int i, j;
    int n1 = keywords.size();
    int n2 = content.size();
    #pragma omp parallel for num_threads(num_t) private(i, j, count) shared(content, keywords, n1, n2)
    for(i=0; i<n1; i++)
    {
        count = 0;
        for(j=0; j<n2; j++)
        {
            string s = content[j];
            stringstream ss(s);
            while(ss >> s)
            {
                if(s == keywords[i])
                {
                    count++;
                }
            }
        }
        #pragma omp critical
        cout << keywords[i] << " " << count << endl;
    }
}

int main()
{
    struct timespec start, end;
    ifstream fin_search, fin_keyword;
    string fname_s, fname_k;
    vector<string> keywords;
    vector<string> content; 
    string word;
    int num_t;
    int n = 0;
    cout << "Enter the search file name: ";
    cin >> fname_s;
    cout << "Enter the keyword file name: ";
    cin >> fname_k;
    fin_search.open(fname_s);
    fin_keyword.open(fname_k);
    while(fin_search)
    {
        string s;
        getline(fin_search, s);
        content.push_back(s);
        n++;
    }
    while(fin_keyword)
    {
        string s;
        getline(fin_keyword, s);
        if(s != "")
            keywords.push_back(s);
    }

    fin_search.close();
    fin_keyword.close();
    cout << "Enter the number of threads: ";
    cin >> num_t;
    omp_set_num_threads(num_t);
    clock_gettime(CLOCK_REALTIME, &start);
    count_word(content, keywords, num_t);
    clock_gettime(CLOCK_REALTIME, &end);
    cout << "Time taken: " << (end.tv_sec - start.tv_sec) * 1000000000 + (end.tv_nsec - start.tv_nsec) << " ns" << endl;
    //cout << content << endl;
}
