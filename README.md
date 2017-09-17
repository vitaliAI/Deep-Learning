# Artificial Neural Networks with C++ from Scratch and ANN with Python using Keras Interface to Tensorflow Library


## Training	the	ANN	with	Stochastic	Gradient	Descent

Step1: 

Randomly	initialise	the	weights	to	small	numbers	close	to	0	BUT	not	0

Step2:

Input	the	first	observation	of	your	dataset	in	the	input	layer.	Each	Feature	is	assigned	one	
Neuron/Node

Step3:

Forward	propagation	is	applied,	where	the	input	from	left	is	propagated	to	the	right.	
Neurons/Nodes	are	activated	depending	on	the	weights	and	threshold	of	the	activation	
function

Step4:

Compare	the	predicted	result	with	the	target	value.	Calculate	the	error

Step5:

Backpropagation	is	from	right	to	left.	The	error	is	back	propagated	and	the	weights	are	
adjusted	to	how	much	they	are	responsible	for	the	error

Step6:

Repeat	Steps	1	to	5	and	update	the	weights

Step7:

When	the	whole	training	set	passed	through	the	ANN,	that	makes	an	epoch.	Redo	more	
epochs.
