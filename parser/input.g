# Comments begin with pound sign 
# Grammar must have name, non-terminal, terminal alphabet, start symbol
# and a least one rule where the leftpart is the start symbol.
# Every line, except with comments and the $ must end with a semicolon
# Note: bos and eof are reserved symbols 
!name:  Sample;
!start: S; 
!non-terminals: S X Y Z;
!terminals: a b;
# rules are in one of the three following forms
# there is only one rule per line
1: S => X|Y|Z;
2: X => b;
3: X => a;
4: Z =>; # lambda rule
# The dollar sign signals the end of the grammar
$
