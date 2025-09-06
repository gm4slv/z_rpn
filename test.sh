!/bin/bash


 FOR A STACK : SIZE = 10

 1.01 2.02
 3.03 4.03
 5.05 6.06
 7.07 8.08
 9.09 10.10
 11.11 12.12
 13.13 14.14
 15.15 16.16
 17.17 18.18
 19.19 20.20
 21.21 22.22
 add
 mult
 uvec
 9.09 10.10
 invert
 subtract
 roll-down [
 last x
 divide
 last x
 x<>y ]
 100.101 @100.101
 mult
 dot
 x<>y ]
 last x
 cross



  OUTPUT : 



echo -e "1.01\n2.02\n3.03\n4.04\n5.05\n6.06\n7.07\n8.08\n9.09\n10.1\n11.11\n12.12\n13.13\n14.14\n15.15\n16.16\n17.17\n18.18\n19.19\n20.20\n21.21\n22.22\na\nm\nu\n9.09\n10.10\ni\ns\n[\nl\ns\nl\n]\n100.101\n100.101\nm\n.\n]\nl\nx\nq\n" | valgrind ./zrpn




