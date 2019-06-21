/******************************************************************************
 -  domain:     Sphere online judge
 -  contest:    list of classical problems
 -  problem:    ONP - Transform the Expression
 -  link:       https://www.spoj.com/problems/ONP/
 -  hash:       $$$$$$$$$$name

 -  author:     Vitor SRG
 -  version:    $$$$$$$$$$date

 -  tags:       tests parse expression stack string infix-postfix

 -  language:   C++14
 ******************************************************************************/


/* Please contact for the solution */
 

/******************************************************************************
 -  test:
    input:      |
                3
                (a+(b*c))
                ((a+b)*(z+x))
                ((a+t)*((b+(a+c))^(c+d)))
    output:     |
                abc*+
                ab+zx+*
                at+bac++cd+^*
 ******************************************************************************/
