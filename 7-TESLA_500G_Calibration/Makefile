#	Run/lego
# gen%: gen%.cc
# #	compile script
# 	g++ -O $@.cc -o $@ \
# 	-I/home/muffin/0-software/pythia8312/include `root-config --cflags` \
# 	-I/home/muffin/0-software/fjcore-3.4.3/ \
# 	-I/home/muffin/0-software/lhapdf-install-6.5.0/include \
# 	-lpythia8 -L/home/muffin/0-software/pythia8312/lib `root-config --glibs` \
# 	-lLHAPDF -L/home/muffin/0-software/lhapdf-install-6.5.0/lib
# #	run the scipt
# 	./$@

#	Run/work
gen%: gen%.cc
#	compile script
	g++ -O $@.cc -o $@ \
	-I/home/pmathew/software/pythia8313/include `root-config --cflags` \
	-lpythia8 -L/home/pmathew/software/pythia8313/lib `root-config --glibs` \
	-I/home/pmathew/software/fjcore-3.4.3/ \
	`/home/pmathew/software/fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` \
	-lLHAPDF -L/home/pmathew/software/lhapdf-install-6.5.0/lib
#	execute script
	./$@
#	delete exe file
	rm -f $@

cut%: cut%.cc
#	compile script
	g++ -O $@.cc -o $@ \
	-I/home/pmathew/software/pythia8313/include `root-config --cflags` \
	-lpythia8 -L/home/pmathew/software/pythia8313/lib `root-config --glibs` \
	-I/home/pmathew/software/fjcore-3.4.3/ \
	`/home/pmathew/software/fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` \
	-lLHAPDF -L/home/pmathew/software/lhapdf-install-6.5.0/lib
#	execute script
	./$@
#	delete exe file
	rm -f $@

# -I/home/muffin/0-software/fastjet-install/bin/fastjet-config `--cxxflags --libs --plugins`