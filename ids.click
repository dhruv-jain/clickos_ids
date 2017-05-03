eth0::FromDevice(0);
eth1::FromDevice(1);

ids::IDS;

c::Classifier(
12/0800,
-
);

c2::Classifier(
12/0800,
-
);

f1::IPFilter(0 src host 192.168.1.95, 1 all)
f2::IPFilter(0 src host 192.168.1.96, 1 all)

eth0 ->  c;
c[0] -> CheckIPHeader(14) -> f1;
f1[0] -> [0]ids[0] -> SimpleQueue(1000) -> ToDevice(0);
f1[1] -> Discard;
c[1] -> Discard;


eth1 -> c2;
c2[0] -> CheckIPHeader(14) -> f2;
f2[0] -> [1]ids;
f2[1] -> Discard;
c2[1] -> Discard;
