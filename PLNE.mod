# donnees

param n; # nombre de fournisseur
param m; # nombre de client
param F{i in 1..n}; # cout ouverture fournisseur
param C{i in 1..n, j in 1..m}; # cout fournir client

# variables
var x{i in 1..n, j in 1..m} binary;
var y{i in 1..n} binary;

# objectif
minimize f: (sum {i in 1..n} F[i]*y[i]) + (sum {i in 1..n, j in 1..m} C[i,j]*x[i,j]) ;

# contrainte
subject to C1{i in 1..n, j in 1..m}: x[i,j] <= y[i];
subject to C2{j in 1..m}: sum{i in 1..n} x[i,j] = 1;
subject to C3{i in 1..n, j in 1..m}: x[i,j] >= 0;

end;
