#include <click/config.h>
#include "ids.hh"
#include <click/glue.hh>
#include <click/args.hh>
#include <click/error.hh>
#include <click/straccum.hh>
#ifdef CLICK_LINUXMODULE
# include <click/cxxprotect.h>
CLICK_CXX_PROTECT
# include <linux/sched.h>
CLICK_CXX_UNPROTECT
# include <click/cxxunprotect.h>
#include <bits/stdc++.h>
#endif
CLICK_DECLS
HashTable<String, String> h(0);

IDS::IDS()
{
 h["Yang"]="Yang";
 h["Yilang"]="Yilang";
 h["Dhruv"]="Dhruv";
 h["Anuku"]="Anukul";
}

void 
IDS::lpsCalculation(int *lps, int patLen, char *pat);

bool
IDS::bool patternMatch(char *pat, char *data)
{
	int patLen = strlen(pat);
	int dataLen = strlen(data);
	
	int lps[patLen];
	
	lpsCalculation(lps, patLen, pat);
	
	int i=0;
	int j=0;
	
	while(i<dataLen){
		if(pat[j]==data[i]){
			j++;
			i++;
		}
		if(j==patLen){
			return true;
			j=lps[j-1];
		}
		else if(i<dataLen&&pat[j]!=data[i]){
			if(j!=0){
				j=lps[j-1];
			}
			else{
				i=i+1;
			}
		}
	}
}

void 
IDS::lpsCalculation(int *lps, int patLen, char *pat)
{
	int len = 0;
	lps[0] = 0;
	
	int i=1;
	while(i<patLen){
		if(pat[i]==pat[len]){
			len++;
			lps[i]=len;
			i++;
		}
		else{
			if(len!=0){
				len=lps[len-1];
			}
			else{
				lps[i]=0;
				i++;
			}
		}
	}
}

int
IDS::configure(Vector<String> &conf, ErrorHandler* errh)
{
  bool timestamp = false;
#ifdef CLICK_LINUXMODULE
  bool print_cpu = false;
#endif
  bool print_anno = false, headroom = false, bcontents;
  _active = true;
  String label, contents = "ASCII";
  int bytes = 24;

    if (Args(conf, this, errh)
	.read_p("LABEL", label)
	.read_p("MAXLENGTH", bytes)
	.read("LENGTH", Args::deprecated, bytes)
	.read("NBYTES", Args::deprecated, bytes)
	.read("CONTENTS", WordArg(), contents)
	.read("TIMESTAMP", timestamp)
	.read("PRINTANNO", print_anno)
	.read("ACTIVE", _active)
	.read("HEADROOM", headroom)
#if CLICK_LINUXMODULE
	.read("CPU", print_cpu)
#endif
	.complete() < 0)
	return -1;

    if (BoolArg().parse(contents, bcontents))
      _contents = bcontents;
  else if ((contents = contents.upper()), contents == "NONE")
      _contents = 0;
  else if (contents == "HEX")
      _contents = 1;
  else if (contents == "ASCII")
      _contents = 2;
  else
      return errh->error("bad contents value '%s'; should be 'NONE', 'HEX', or 'ASCII'", contents.c_str());

  _label = label;
  _bytes = bytes;
  _timestamp = timestamp;
  _headroom = headroom;
  _print_anno = print_anno;
#ifdef CLICK_LINUXMODULE
  _cpu = print_cpu;
#endif
  return 0;
}

void 
IDS::push(int port, Packet* p) {

	if (0 == port) {
           // traffic
           printf("traffic:");
       	  if(matcher(p))
		printf("yes\n\n");
	  else
		printf("no\n\n");
         checked_output_push(0,p);
        } else {
           // policy
         printf("policy:");
       	/**if(matcher(p))
		printf("yes\n");
	else
		printf("no\n");**/
 	modiPolicy(p);
	p->kill();

        }


}

bool IDS::matcher(Packet* p){
 String patterns[4] = {"Yilang","Yang","Dhruv","Anukul"};
 int bytes = p -> length();
    StringAccum sa(3 * bytes);
    char *buf = sa.data() + sa.length();
        const unsigned char *data = p->data();
    for (int i = 0; i < bytes; i++, data++) {
 //               if ((i % 8) == 0)
  //                  *buf++ = ' ';
    //            if (*data < 32 || *data > 126)
      //              *buf++ = '.';
        //        else
                    *buf++ = *data;
        }
    sa.adjust_length(buf - (sa.data() + sa.length()));
    char targetstr[51];
    memcpy(targetstr, &sa.c_str()[54], 50);
    targetstr[50] = '\0';

    click_chatter("%s", &targetstr[0]);

 const char* found;
 for(HashTable<String, String>::iterator it=h.begin();it;++it){
 char *a = targetstr.c_str();
 found = patternMatch(*a,it.value().c_str());
 if(found){
  return true;}
 }
  return false;
}

void IDS::modiPolicy(Packet* p){

 int bytes = p -> length();
    StringAccum sa(3 * bytes);
    char *buf = sa.data() + sa.length();
        const unsigned char *data = p->data();
    for (int i = 0; i < bytes; i++, data++) {
 //               if ((i % 8) == 0)
  //                  *buf++ = ' ';
    //            if (*data < 32 || *data > 126)
      //              *buf++ = '.';
        //        else
                    *buf++ = *data;
        }
    sa.adjust_length(buf - (sa.data() + sa.length()));
    char targetstr[51];
    memcpy(targetstr, &sa.c_str()[54], 50);
    targetstr[50] = '\0';
    String po(targetstr);
    if(h.get(po)){
      h.erase(po);
      printf("delete pattern:\n");
    }
    else{
      h[po]=po;
      printf("add pattern\n");
    }
   click_chatter("%s\n\n", po.c_str());
   
}

void
IDS::add_handlers()
{
    add_data_handlers("active", Handler::OP_READ | Handler::OP_WRITE | Handler::CHECKBOX | Handler::CALM, &_active);
}

CLICK_ENDDECLS
EXPORT_ELEMENT(IDS)
ELEMENT_MT_SAFE(IDS)
