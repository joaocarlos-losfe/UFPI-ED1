/*
por João Carlos de Sousa Fé. 01/04/2021

A): "px" aponta para o ENDEREÇO de "x", logo qualquer alteração no CONTEÚDO
de "px" ira refletir diretamente no CONTEÚDO de x.

B): "px" e "py" ambos esperam receber um ENDEREÇO DE MEMORIA das variaveis 
"x" e "y" respectivamente. Por tanto, nesse caso, não diferenca, ja que ambos
esperam receber ENDEREÇO DE MEMORIA

C): "x" deve imprimir o valor 500, "&x" deve imprimir seu endereço em hexadecimal 
(notação "%p") de "x" (algo como 0060FEF4) , "px" deve imprimir o endereço de "x"
(nesse caso por exemplo: 0060FEF4). "y" debe imprimir o valor de x (500) acrescido
de 200: 500 + 200, logo a saida de y sera 700.

saida do printf esperada: x = 500, End. x = 0060FEF4, px = 0060FEF4, y = 700


D): o CONTEÚDO para onde "px" APONTA é alterado para o conteúdo de y, nesse caso
fica "*px" na função "altera1" recebeu o valor de y, 700. o CONTEÚDO de "y"
(valor: 700) é acrescido em mais 50, logo o CONTEUDO "y" passa a ser 750.

Saida do printf esperada: x = 700, End. x = 0060FEF4, px = 0060FEF4, y = 750. 


E): será impresso primeiramente o valor de "y", alterado anteriormente pela funão "altera1",
nesse caso o valor 750 será impresso. o ENDEREÇO de "y" será impresso em seguida (algo como 0FEF4).
em seguida será impresso o ENDEREÇO DE MEMÓRIA de "y" apontado por "py" (0FEF4). Ao final será impresso
a valor de X, que será 700.

Saida do printf esperada: y = 750, End. y = 0FEF4, py = 0FEF4, x = 700


F): o valor de "y" será impresso (ainda 750). O endereço apontando por "py" será impresso (ainda 0FEF4).
"py" dentro da função "altera2" passa a apontar para o ENDEREÇO de "x", logo qualquer alteração
no CONTEUDO DE "py" irá refletir diretamente no CONTEÚDO de "x". ao imprimir o "py", sera impresso
algo como "0060FEF4", que é o endereço de "x" agora "apontado" por "py". "x" (com CONTEÚDO "700") 
dentro da função "altera2" é somado com 300. 
"x" agora, o seu valor CONTEÚDO passa a ser 1000.

saida esperada: y = 750, End. y = 0FEF4, py = 0060FEFC, x = 1000


G): na função "altera1" somente é alterado o CONTEUDO das variaveis repassadas.
ja na função altera2, o endereço apontando por "py" é alterado, APONTANDO diretamente para
o ENDEREÇO de "x", em seguida o CONTEUDO de x é alterado.

*/