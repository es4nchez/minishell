# minishell

Pour la compil : gc minishell.c dir_name.c input.c handle_input.c ft_substr.c ft_strncmp.c ft_strlen.c execve_threading.c env_function.c -lreadline -o minishell && ./minishell

Comme d'ab, mais il faut le -lreadline pour utiliser la fonction readline

Idée de Workflow ( à modifier ) :

* -> le shell tourne continuellement avec le while(1)
* -> on parse l'input pour avoir la commande + les arguments + les pipes/autres si il y en a
* -> on détecte si c'est 1) un builtin ou 2) une commande du bin
* -> si 1) on execute la commande normal pépère
* -> si 2) on fork le process pour pouvoir retourner au shell après l'exécution
* -> back to beginning

To do :

* Les ctrl+c / ctrl+z etc..
* Les pipes
* Du parsing propre
* So much more
