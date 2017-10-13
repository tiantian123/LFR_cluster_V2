#include <assert.h>  
#include <map>  
#include <vector>  
#include <string>  
#include <stdio.h>  
#include <iostream>  
using namespace std;  
typedef unsigned long   u32;  
  
class OperateCSV  
{  
private:  
    map<u32, map<u32, string>> m_stringMap;  
    string m_CSVName;  
public:  
    OperateCSV(){}  
    OperateCSV(const char *path)  
    {  
        assert(LoadCSV(path));  
    }  
    ~OperateCSV(){}  
  
    bool LoadCSV(const char *path);  
    bool SaveCSV(const char *path = NULL);  
  
    bool GetIntValue(u32 uiRow, u32 uiCol, int &riValue);  
    bool GetFloatValue(u32 uiRow, u32 uiCol, float &rfValue);  
    string* GetStringValue(u32 uiRow, u32 uiCol);  
  
    int GetParamFromString(string str, vector<string> &stringVec, char delim  = ',');//���ݶ��ţ������ַ����ķָ�  
  
    map<u32, map<u32, string>>& GetCSVMap()  
    {  
        return m_stringMap;  
    }  
};  
  
  
bool OperateCSV::LoadCSV(const char *path)  
{  
    FILE *pFile = fopen(path, "r");  
  
    if (pFile)  
    {  
        fseek(pFile, 0, SEEK_END);//�ض�λ���ϵ��ļ�ָ��.�������ǽ�λ��ָ���Ƶ����ļ�ͷ0���ֽڴ����������ļ���ͷ  
        u32 uSize = ftell(pFile);//������ȡ�ļ��ĵ�ǰ��дλ��,����ֵ�ǵ�ǰ��дλ��ƫ���ļ�ͷ�����ֽ���.���Ժ���������  
        rewind(pFile);//ʹ�ļ�pFile��λ��ָ��ָ���ļ���ʼ��  
  
        char *fileBuffer = new char[uSize];//  
        fread(fileBuffer, 1, uSize, pFile);//��������һ�����ݿ�  
  
        map<u32, string> stringMap;  
        u32 uiIndex = 1;  
  
        char *pBegin = fileBuffer;//�ַ������׵�ַ  
        char *pEnd = strchr(pBegin, '\n');//��һ���ַ����в���һ���ض����ַ�  
  
  
        pBegin = pEnd + 1;//�ڶ��е���ʼ�������˵�һ��  
        pEnd = strchr(pBegin, '\n');  
  
        while (pEnd)  
        {  
            string strTemp;  
            strTemp.insert(0, pBegin, pEnd-pBegin);  
            assert(!strTemp.empty());  
            stringMap[uiIndex++] = strTemp;//��ÿһ�е��ַ����浽map�У�keyΪ˳��ţ�valueΪ�ַ���  
            pBegin = pEnd + 1;  
            pEnd = strchr(pBegin, '\n');//Ѱ����һ��  
        }  
        delete []fileBuffer;  
        fileBuffer = NULL;  
        pBegin = NULL;  
        pEnd = NULL;  
  
        map<u32, string>::iterator iter = stringMap.begin();//����ÿһ���ַ���  
        for (; iter != stringMap.end(); ++iter)  
        {  
            vector<string> stringVec;//�洢���ն��ŷָ��õ�����  
            map<u32, string> stringMapTemp;  
            assert(GetParamFromString(iter->second, stringVec) > 0);  
  
            vector<string>::size_type idx = 0;  
            for (; idx != stringVec.size(); ++idx)  
            {  
                stringMapTemp[idx + 1] = stringVec[idx];//  
            }  
  
            m_stringMap[iter->first] = stringMapTemp;//ÿһ�еĴ洢���  
        }  
  
        fclose(pFile);  
        m_CSVName = path;  
        return true;  
    }   
    else  
    {  
        return false;  
    }  
}  
  
bool OperateCSV::SaveCSV(const char *path /* = NULL */)  
{  
    if (path != NULL)  
    {  
        m_CSVName = path;  
    }  
  
    FILE *pFile = fopen(m_CSVName.c_str(), "w");  
    if (pFile)  
    {  
        map<u32, map<u32, string>>::iterator iter = m_stringMap.begin();  
        for (; iter != m_stringMap.end(); ++iter)  
        {  
            map<u32, string> &rStringMap = iter->second;  
            map<u32, string>::iterator it = rStringMap.begin();  
            for (; it != rStringMap.end(); ++it)  
            {  
                string strTemp = it->second;  
                strTemp += ',';  
                fwrite(strTemp.c_str(), 1, 1, pFile);  
            }  
  
            char delim = '\n';  
            fwrite(&delim, 1, 1, pFile);  
        }  
  
        fclose(pFile);  
        return true;  
    }   
    else  
    {  
        return false;  
    }  
}  
  
bool OperateCSV::GetIntValue(u32 uiRow, u32 uiCol, int &riValue)  
{  
    string *pStr = GetStringValue(uiRow, uiCol);  
    if (pStr)  
    {  
        riValue = atoi(pStr->c_str());  
        return true;  
    }   
    else  
    {  
        return false;  
    }  
}  
  
bool OperateCSV::GetFloatValue(u32 uiRow, u32 uiCol, float &rfValue)  
{  
    string *pStr = GetStringValue(uiRow, uiCol);  
    if (pStr)  
    {  
        rfValue = atof(pStr->c_str());  
        return true;  
    }   
    else  
    {  
        return false;  
    }  
}  
  
string* OperateCSV::GetStringValue(u32 uiRow, u32 uiCol)  
{  
    map<u32, map<u32, string>>::iterator iter = m_stringMap.find(uiRow);//��Ϊ�պ��к�Ϊ�ؼ��֣����Կ�����find���в���  
    if (iter != m_stringMap.end())  
    {  
        map<u32, string> &rStrMap = iter->second;  
        map<u32, string>::iterator it = rStrMap.find(uiCol);  
        if (it != rStrMap.end())  
        {  
            return &(it->second);  
        }   
        else  
        {  
            return NULL;  
        }  
    }   
    else  
    {  
        return NULL;  
    }  
}  
  
//���ڷָ��ַ�������CSV����е�һ�а��չ��������һ���ַ������洢��һ��vector��  
//����CSV��������洢�����ݵĲ�ͬ�����ظ�����  
int OperateCSV::GetParamFromString(string str, vector<string> &stringVec, char delim)  
{  
    char *token = strtok(const_cast<char *>(str.c_str()), &delim);  
    while (token)  
    {  
        string strTemp = token;  
        stringVec.push_back(strTemp);  
        token = strtok(NULL, &delim);  
    }  
  
    return stringVec.size();  
}  
  
  
void main()  
{  
    OperateCSV cs("9_9-1.csv");  
    map<u32, map<u32, string>> stringMap = cs.GetCSVMap();  
  
    map<u32, map<u32, string>>::iterator iter = stringMap.begin();  
    for (; iter != stringMap.end(); ++iter)  
    {  
        map<u32, string> strmap = iter->second;  
        map<u32, string>::iterator it = strmap.begin();  
        for (; it != strmap.end(); ++it)  
        {  
            cout<<it->second<<"  ";  
        }  
            cout<<endl;  
    }  
    string *ss=cs.GetStringValue(2,1);  
    string st = ss->c_str();  
    cout<<*ss<<" "<<st<<endl;  
}