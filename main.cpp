#include "IPGetter.cpp"
#include "uson.cpp"
#include "sdk.cpp"
#include <unistd.h>

USON config;
DOMAIN dnsinfo;
string IPv4,IPv6;

enum IPChange
{
	ipv4,
	ipv6,
	both,
	none
};

void ReadConfig()
{
	int ret = config.ReadFile("./config.uson");
	if(ret!=0)
	{
		cout<<"Cannot load 'config.uson'"<<endl;
		exit(ret);
	}
	ret = dnsinfo.LoadFile(config["DNS_FILE_PATH"]);
	if(ret!=0)
	{
		cout<<"Cannot load '"<<config["DNS_FILE_PATH"]<<"'"<<endl;
		exit(ret);
	}
	return;
}

IPChange UpdateIP()
{
	string v4,v6;
	v4=IP::IPv4();
	v6=IP::IPv6();
	if(IPv4==v4 && IPv6==v6)
	{
		return none;
	}
	else if(IPv4!=v4 && IPv6!=v6)
	{
		IPv4=v4;
		IPv6=v6;
		return both;
	}
	else if(IPv4!=v4)
	{
		IPv4=v4;
		return ipv4;
	}
	else
	{
		IPv6=v6;
		return ipv6;
	}
	return none;
}

string SwitchIP(string type)
{
	if(type=="A")
		return IPv4;
	else if(type=="AAAA")
		return IPv6;
	return IPv4;
}

string IPNotChangeLog()
{
	time_t ti;
        time(&ti);
        tm* lt=localtime(&ti);
        int year=lt->tm_year+1900;
        int month=lt->tm_mon+1;
        int day=lt->tm_mday;
        int hour=lt->tm_hour;
        int minute=lt->tm_min;
	int second=lt->tm_sec;
	int size=60+IPv4.length()+IPv6.length();
	char* recv=new char[size];
	sprintf(recv,"IP Doesn't change at %04d-%02d-%02d %02d:%02d:%02d.\nIPv4:%s\nIPv6%s\n",year,month,day,hour,minute,second,IPv4.c_str(),IPv6.c_str());
	string ret=recv;
	delete[] recv;
	return ret;
}

int UpdateDomainRecord()
{
	IPChange ipc;
	ipc=UpdateIP();
	if(ipc==none)
		return -1;//IP_NOT_CHANGE
	string domain,sub,dns;
	SDK sdk(config["ACCESS_KEY_ID"],config["ACCESS_KEY_SERCET"],config["LOG_FILE_PATH"]);
	if(ipc==both)
	{
		for(int i=0;i<dnsinfo.GetDomainCount();i++)
		{
			domain=dnsinfo.GetDomain(i);
			for(int j=0;j<dnsinfo.GetSubCount(domain);j++)
			{
				sub=dnsinfo.GetSubName(domain,j);
				dns=dnsinfo.GetDNSType(domain,sub);
				sdk.UpdateDomainRecord(domain,sub,dns,SwitchIP(dns));
			}
		}
		return 0;//BOTH_IP_CHANGED
	}
	else if(ipc==ipv4)
	{
		for(int i=0;i<dnsinfo.GetDomainCount();i++)
		{
			domain=dnsinfo.GetDomain(i);
			for(int j=0;j<dnsinfo.GetSubCount(domain);j++)
			{
				sub=dnsinfo.GetSubName(domain,j);
				dns=dnsinfo.GetDNSType(domain,sub);
				if(dns=="AAAA")
					continue;
				sdk.UpdateDomainRecord(domain,sub,dns,SwitchIP(dns));
			}
		}
		return 4;//IPV4_CHANGED
	}
	else if(ipc==ipv6)
	{
		for(int i=0;i<dnsinfo.GetDomainCount();i++)
		{
			domain=dnsinfo.GetDomain(i);
			for(int j=0;j<dnsinfo.GetSubCount(domain);j++)
			{
				sub=dnsinfo.GetSubName(domain,j);
				dns=dnsinfo.GetDNSType(domain,sub);
				if(dns=="A")
					continue;
				sdk.UpdateDomainRecord(domain,sub,dns,SwitchIP(dns));
			}
		}
		return 6;//IPV6_CHANGED
	}
	else
		return -2;
	return -3;
}

int main()
{
	int res;
	ReadConfig();
	fstream f(config["LOG_FILE_PATH"].c_str(),ios::in);
	if(!f.is_open())
	{
		f.close();
		f.open(config["LOG_FILE_PATH"].c_str(),ios::out);
		f<<"DDNS Version 1.0.0 Operation Log"<<endl<<endl;
		f.close();
	}
	while(true)
	{
		res = UpdateDomainRecord();
		if(res==-1)
		{
			f.open(config["LOG_FILE_PATH"].c_str(),ios::out|ios::app);
			f<<IPNotChangeLog()<<endl;
			f.close();
		}
		sleep(30000);
	}
	return 0;
}
