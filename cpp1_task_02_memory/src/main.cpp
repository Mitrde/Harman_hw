#include <iostream>
using namespace std;
#include <cstring> 
#pragma warning(disable:4996)

const char* strreplace(char *pszResult, const char *pcszSubstr, const char *pcszStr2)
{
	const char *tmp = pszResult;  //pointer to source string
	int max_size = ((strlen(pszResult) / strlen(pcszSubstr) + 1)*strlen(pcszStr2)< strlen(pszResult))?
		strlen(pszResult) : (strlen(pszResult) / strlen(pcszSubstr) + 1)*strlen(pcszStr2);
	char *result = new char[max_size];
	char *tmp2 = result;          //pointer to result string
	if (strstr(tmp, pcszSubstr) == nullptr)	
		return pszResult;
	
	while (true)
	{
		while (strstr(tmp, pcszSubstr) != tmp)
		{			
			*tmp2 = *tmp;
			tmp++;
			tmp2++;			
		}
		for (size_t i = 0; i < strlen(pcszStr2); i++)
		{
			*(tmp2 + i) = *(pcszStr2 + i);
		}
		tmp2 += strlen(pcszStr2);
		tmp += strlen(pcszSubstr);

		if (strstr(tmp, pcszSubstr) == nullptr)
		{
			while (*tmp != '\0')
			{
				*tmp2 = *tmp;
				tmp2++;
				tmp++;
			}
			*tmp2 = '\0';			
			strcpy(pszResult, result);
			delete [] result;			
			return pszResult;
		}
	}
}




int main()
{
	int MAX = 1000;
	char* src_string = new char[MAX];
	char *sub_string = new char[MAX];
	char *str2 = new char[MAX];;
	
	cout << "input source string: " << endl;
	cin.getline(src_string, MAX);
	cout << "input substring: " << endl;
	cin.getline(sub_string, MAX);
	cout << "input replacement string: " << endl;
	cin.getline(str2, MAX);


	//char* tmp = strreplace("ABABCDCDCD--ABABCD__", "ABCD", "0AB");
	const char* tmp = strreplace(src_string, sub_string, str2);
	cout << tmp << endl;
	delete []src_string;
	delete []sub_string;
	delete []str2;
	

	system("pause");
}
