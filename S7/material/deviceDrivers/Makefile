obj-m += myDriver1.o myDriver2.o

# all rule: checks if the source code for myDriver1 or myDriver2 
# have changed since last compilation and generate two linux modules 
# if needed: myDriver1.ko  myDriver2.ko

# clean rule: deletes files generated in last compilation of myDriver1 
# and myDriver2

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
