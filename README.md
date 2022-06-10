# minishell

Pour la compil : make && ./minishell

Idée de Workflow ( à modifier ) :

* -> le shell tourne continuellement avec le while(1)
* -> on parse l'input pour avoir la commande + les arguments + les pipes/autres si il y en a
* -> on détecte si c'est 1) un builtin ou 2) une commande du bin
* -> si 1) on execute la commande normal pépère
* -> si 2) on fork le process pour pouvoir retourner au shell après l'exécution
* -> back to beginning

To do :

* les perror etc + code de sortie
* Les pipes
* Du parsing propre
