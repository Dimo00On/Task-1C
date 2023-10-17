# Коньков Дмитрий Алексеевич
# Задача 2
# Запустить скрипт для сборки ./install.sh и затем запустить файл bin/Task1C, после чего ему написать количество рёбер графа и сами рёбра
# Для маленьких графов используется полный перебор возможных заражённых городов, и находится точное решение. Для больших графов сначала заражаются города, соседние с соседями уже заражённых городов и не соседние с заражёнными, чтобы у соседей заражённых городов оказалось 2 заражённых соседних города и началась эпидемия, и при этом заразился ещё один город(который мы только что заразили) без использования своих соседей. Если таких нет, то заражается город среди соседей заражённых, чтобы началась эпидемия из-за наличия 2 заражённых городов, так как этот вариант чуть хуже, чем прошлый, так как текущий город возможно мог быть заражён с помощью эпидемии, а не изначально. Если же и соседей заражённых городов не осталось, то берётся следующий город из оставшихся(который не связан с заражённой компонентой). Города берутся, пока не останется незаражённых городов.
# Алгоритмы лежат в классе SolutionFinder, базовая информация о графе лежит в Graph.
