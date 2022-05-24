cmd_/home/kanaka/jyothi/chardriver/modules.order := {   echo /home/kanaka/jyothi/chardriver/simple_char.ko; :; } | awk '!x[$$0]++' - > /home/kanaka/jyothi/chardriver/modules.order
