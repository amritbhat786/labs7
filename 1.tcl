set ns [new Simulator]
set f [open out1.tr w]
set nf [open out1.nam w]

$ns color 1 "Blue"
$ns color 2 "Red"

$ns trace-all $f
$ns namtrace-all $nf

proc finish {} {
	global ns f nf
	$ns flush-trace
	close $f
	close $nf
	exec nam out1.nam &
	exit 0
}
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$n0 label "UDP Source"
$n1 label "TCP Source"
$n2 label "TCP & UDP Source"

$ns duplex-link $n0 $n2 0.1Mb 10ms DropTail
$ns duplex-link $n1 $n2 0.1Mb 10ms DropTail

$ns duplex-link-op $n0 $n2 orient right 
$ns duplex-link-op $n1 $n2 orient down
$ns queue-limit $n1 $n2 20

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0
$udp0 set class_ 1

set cbr0 [new Application/Traffic/CBR]
$cbr0 attach-agent $udp0
$udp0 set class_ 2
$udp0 set packetSize_ 500
$udp0 set interval_ 0.001

set tcp0 [new Agent/TCP]
$ns attach-agent $n1 $tcp0
$tcp0 set class_ 2

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0
$ftp0 set maxPkts_ 1000

set null0 [new Agent/Null]
$ns attach-agent $n2 $null0

set sink [new Agent/TCPSink]
$ns attach-agent $n2 $sink
$ns connect $udp0 $null0
$ns connect $tcp0 $sink

$ns at 0.5 "$cbr0 start"
$ns at 1.0 "$ftp0 start"
$ns at 4.0 "$ftp0 stop"
$ns at 4.5 "$cbr0 stop"
$ns at 5.0 "finish" 

$ns run
