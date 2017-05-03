#ifndef CLICK_ids_HH
#define CLICK_ids_HH
#include <click/element.hh>
#include <click/string.hh>
#include <click/hashtable.hh>
CLICK_DECLS
class IDS : public Element { 
 public:
    IDS() CLICK_COLD;
    const char *class_name() const		{ return "IDS"; }
    const char *port_count() const		{ return "2/1"; }
    int configure(Vector<String> &, ErrorHandler *) CLICK_COLD;
    bool can_live_reconfigure() const		{ return true; }
    const char* processing() const { return "hh/h"; }
    void add_handlers() CLICK_COLD;
    void push(int, Packet*);
    bool matcher(Packet*);	
    void modiPolicy(Packet*);
 private:
    String _label;
    int _bytes;		// How many bytes of a packet to print
    bool _active;
    bool _timestamp : 1;
    bool _headroom : 1;
#ifdef CLICK_LINUXMODULE
    bool _cpu : 1;
#endif
    bool _print_anno;
    uint8_t _contents;
    uint32_t counter;
};
CLICK_ENDDECLS
#endif
