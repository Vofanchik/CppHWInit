#include <iostream>
#include <string>
using namespace std;
void computeLPS(string pat, int* lps) 
{
    int j = 0;

    lps[0] = 0; // lps[0] is always 0 

    int i = 1;
    while (i < pat.size()) {
        if (pat[i] == pat[j]) {
            j++;
            lps[i] = j;
            i++;
        }
        else
        {
            if (j != 0) {
                j = lps[j - 1];
            }
            else
            {
                lps[i] = 0;
                i++;
            }
        }
    }
}


void KMPSearch(const string& pat, const string& txt)
{
    int* lps = new int[pat.size()];

    computeLPS(pat, lps);

    int i = 0;
    int j = 0;
    while (i < txt.size()) {
        if (pat[j] == txt[i])
        {
            j++;
            i++;
        }
        if (j == pat.size()) {
            cout << "Found pattern at index" << i - j << endl;
            j = lps[j - 1];
        }
        else if (i < txt.size() && pat[j] != txt[i]) {
            if (j != 0)
            {
                j = lps[j - 1];
            }
            else
            {
                i = i + 1;
            }
        }
    }
}

void IsKPeriodic(int k, const string& txt)
{
    if (k <= 0)
    {
        return;
    }
    else
    {
        string pat;
        pat = txt.substr(0, k);

        int* lps = new int[pat.size()];

        computeLPS(pat, lps);

        int i = 0;
        int j = 0;
        int count = 0;
        while (i < txt.size()) {
            if (pat[j] == txt[i])
            {
                j++;
                i++;
            }
            if (j == pat.size()) {
                count++;
                j = lps[j - 1];
            }

            else if (i < txt.size() && pat[j] != txt[i]) {
                if (j != 0)
                {
                    j = lps[j - 1];
                }
                else
                {
                    i = i + 1;
                }
            }
        }
        if (k * count == txt.size())
            cout << txt << " is periodic" << endl;
        else cout << txt << " not periodic" << endl;
    }
}

int main()
{
    string isp = "abcabcabc"; 
    string np = "abcabcabca";
    string npa = "abcdabcabc";
    int k = 3; 
    IsKPeriodic(k, isp);
    IsKPeriodic(k, np);
    IsKPeriodic(k, npa);
    //string txt = "ABABDABACDABABCABABABABDABACDABABCABAB";
    //string pat = "ABABCABAB";
    //KMPSearch(pat, txt);
    return 0;
}