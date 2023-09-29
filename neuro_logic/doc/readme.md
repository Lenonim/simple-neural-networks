***<h1 align = "center">Решение логических операций</a>***

**<h2> Исследование логических операций на линейную разделимость </h2>** 

![](images/bool_operators.png)  

**<h2> Сеть для линейно разделимых операций </h2>** 

<p align = "justify">

</p>

<p align = "justify">
Для решения логической линейно разделимой задачи подойдёт самая простая модель перспетрона. Его схема приведена ниже. 
</p>

![](images/threshold.png)  

Произведём расчёт сети, использующая пороговую функцию активации:

![](images/thresholdAns.png)  

Для обучения сети воспользуемся дельта-правилом:

![](images/thresholdFit.png)  

**<h2> Сеть для линейно не разделимых операций </h2>** 

<p align = "justify">
Решение для линейно разделимых операций достаточно простое и удалось запрограммировать решение 14 функций, однако такая сеть не способна решить задачи, которые линейно не разделимы. Тогда воспользуемся следующей схемой:
</p>

![](images/signal.png)

Рассчитаем сеть:

![](images/signalAns.png)  

Обучим сеть с помощью обобщённого дельта-правила.  
Обучим выходной нейрон:

![](images/signalFitOut.png)  

Найдём ошибки по выходам нейронов 1 и 2:

![](images/signalFitNeurons.png)  

Обучим нейрон 1:

![](images/signalFitN1.png)  

Обучим нейрон 2:

![](images/signalFitN2.png)  

**<h2> Результаты </h2>** 

![](images/R1.png)  

![](images/R2.png)  

Результаты переобучения на разных данных:

![](images/R3.png)  

Подадим другой тип данных:

![](images/R4.png)  