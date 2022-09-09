b = bubble_sort
m = merge_sort
s = selection_sort
i = insertion_sort

run10000:
		(echo "$(b) => 10000 inputs") 1> time.txt
		(time ./$(b)/$(b) < ./input10000.txt > ./output10000.txt) 2>> time.txt

		(echo "\n\n$(s) => 10000 inputs") 1>> time.txt
		(time ./$(s)/$(s) < ./input10000.txt > ./output10000.txt) 2>> time.txt

		(echo "\n\n$(i) => 10000 inputs") 1>> time.txt
		(time ./$(i)/$(i) < ./input10000.txt > ./output10000.txt) 2>> time.txt

		(echo "\n\n$(m) => 10000 inputs") 1>> time.txt
		(time ./$(m)/$(m) < ./input10000.txt > ./output10000.txt) 2>> time.txt
