// String
string oddHashedString(string s)
{
    string T = "^";
    for (char c : s)
    {
        T += "#" + string(1, c);
    }
    T += "#$";
    return T;
}

string f(string s){
    string T = oddHashedString(s);
    int n = T.length();
    vector<int> P(n, 0);

    int C = 0, R = 0;
    int max_len = 0;
    int center_index = 0;

    for (int i = 1; i < n - 1; i++)
    {
        int i_mirror = 2 * C - i;

        if (i < R) P[i] = min(R - i, P[i_mirror]);

        while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
        {
            P[i]++;
        }

        if (i + P[i] > R)
        {
            C = i;
            R = i + P[i];
        }

        if (P[i] > max_len)
        {
            max_len = P[i];
            center_index = i;
        }
    }

    int start = (center_index - max_len) / 2;
    int end = start + max_len - 1;
    string res = s.substr(start, max_len);
    return res;
}

// Vector
vector<int> oddHashedVector(vector<int> &v)
{
    vector<int> T;
    T.push_back(INT_MIN + 1); // '^'
    for (int x : v) {
        T.push_back(INT_MIN); // '#'
        T.push_back(x);
    }
    T.push_back(INT_MIN);     // '#'
    T.push_back(INT_MIN + 2); // '$'
    return T;
}

vector<int> f(vector<int> &v){
    vector<int> T = oddHashedVector(v);
    int n = T.size();
    vector<int> P(n, 0);

    int C = 0, R = 0;
    int max_len = 0;
    int center_index = 0;

    for (int i = 1; i < n - 1; i++)
    {
        int i_mirror = 2 * C - i;

        if (i < R) P[i] = min(R - i, P[i_mirror]);

        while (T[i + 1 + P[i]] == T[i - 1 - P[i]])
        {
            P[i]++;
        }

        if (i + P[i] > R)
        {
            C = i;
            R = i + P[i];
        }

        if (P[i] > max_len) // can be modified based on ques requirement
        {
            max_len = P[i]; 
            center_index = i;
        }
    }

    int start = (center_index - max_len) / 2;
    int end = start + max_len - 1;
    vector<int> res(v.begin() + start, v.begin() + end + 1);
    return res;
}
