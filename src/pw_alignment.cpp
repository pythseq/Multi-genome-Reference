#include "pw_alignment.hpp"

pw_alignment::pw_alignment(string sample1str, string sample2str, size_t sample1_begin, size_t sample2_begin, size_t sample1_end, size_t sample2_end, size_t sample1reference, size_t sample2reference ): samples(2), begins(2), ends(2), references(2) {
	assert(sample1str.length() == sample2str.length());
	size_t bitlength = 3*sample1str.size();
	samples.at(0).resize(bitlength);
	samples.at(1).resize(bitlength);

	for(size_t i=0; i<sample1str.length(); ++i) {
		char base1 = sample1str.at(i);
		char base2 = sample2str.at(i);
		bool bit1;
		bool bit2;
		bool bit3;
		base_translate(base1, bit1, bit2, bit3);
		samples.at(0).at(3*i) = bit1;
		samples.at(0).at(3*i+1) = bit2;
		samples.at(0).at(3*i+2) = bit3;
		base_translate(base2, bit1, bit2, bit3);
		samples.at(1).at(3*i) = bit1;
		samples.at(1).at(3*i+1) = bit2;
		samples.at(1).at(3*i+2) = bit3;
	}
	vector<bool> sample1;
	vector<bool> sample2;
	begins.at(0) = sample1_begin;
	begins.at(1) = sample2_begin;
	ends.at(0) = sample1_end;
	ends.at(1) = sample2_end;
	samples.at(0) = sample1;
	samples.at(1) = sample2;
	references.at(0) = sample1reference;
	references.at(1) = sample2reference;
}

pw_alignment::pw_alignment() {}

pw_alignment::~pw_alignment() {

}


pw_alignment::pw_alignment(const pw_alignment & p) {

}

size_t pw_alignment::alignment_length() const {
	return samples.at(0).size() / 3;
}


void pw_alignment::alignment_col(size_t c, char & s1, char & s2) const {
	bool bit1;
	bool bit2;
	bool bit3;
	bit1 = samples.at(0).at(3*c);
	bit2 = samples.at(0).at(3*c+1);
	bit3 = samples.at(0).at(3*c+2);
	s1 = base_translate_back(bit1, bit2, bit3);
	bit1 = samples.at(1).at(3*c);
	bit2 = samples.at(1).at(3*c+1);
	bit3 = samples.at(1).at(3*c+2);
	s2 = base_translate_back(bit1, bit2, bit3);
}
void  pw_alignment::set_alignment_bits(vector<bool> s1, vector<bool> s2){
	samples.at(0) = s1;
	samples.at(1) = s2;
}

void pw_alignment::split(bool sample, size_t position, pw_alignment & first_part, pw_alignment & second_part ) const{
	vector<bool> fps1(samples.at(0).size());
	vector<bool> fps2(samples.at(0).size());
	vector<bool> sps1(samples.at(0).size());
	vector<bool> sps2(samples.at(0).size());

cout << "size " << samples.at(0).size() << endl;


	size_t s = 0;
	if (sample == true) {
	for (size_t i=0; i<samples.at(0).size()/3; ++i){
cout << "bits " << samples.at(0).at(i*3) << samples.at(0).at(i*3+1) << samples.at(0).at(i*3+2)<< endl;
 		if (samples.at(0).at(0+i*3)== true && samples.at(0).at(1+i*3)==false && samples.at(0).at(2+i*3)==true) {
cout << "gap at " << i << endl;
			s=s+1;
		}
	fps1.at(3*i) = samples.at(0).at(3*i);
	fps2.at(3*i) = samples.at(1).at(3*i);
	fps1.at(3*i+1) = samples.at(0).at(3*i+1);
	fps2.at(3*i+1) = samples.at(1).at(3*i+1);
	fps1.at(3*i+2) = samples.at(0).at(3*i+2);
	fps2.at(3*i+2) = samples.at(1).at(3*i+2);
	if (i == position-1+s)
		break;
	
}

	fps1.resize(3*(position+s));
	fps2.resize(3*(position+s));
	first_part.set_alignment_bits(fps1,fps2); 

for (size_t i=position+s;i<samples.at(0).size()/3;++i){
      	sps1.at(3*(i-position-s)) = samples.at(0).at(3*i);
	sps2.at(3*(i-position-s)) = samples.at(1).at(3*i);
	sps1.at(3*(i-position-s)+1) = samples.at(0).at(3*i+1);
	sps2.at(3*(i-position-s)+1) = samples.at(1).at(3*i+1);
	sps1.at(3*(i-position-s)+2) = samples.at(0).at(3*i+2);
	sps2.at(3*(i-position-s)+2) = samples.at(1).at(3*i+2);

}

	sps1.resize(samples.at(0).size()-3*(position+s));
	sps2.resize(samples.at(0).size()-3*(position+s));
	cout << "size " << sps1.size() << endl;

	second_part.set_alignment_bits(sps1,sps2);


}

	else{
    for (size_t i=0; i<samples.at(1).size()/3; ++i){
cout << "bits " << samples.at(1).at(i*3) << samples.at(1).at(i*3+1) << samples.at(1).at(i*3+2)<< endl;
 		if (samples.at(1).at(0+i*3)== true && samples.at(1).at(1+i*3)==false && samples.at(1).at(2+i*3)==true) {
cout << "gap at " << i << endl;
			s=s+1;
		}
	fps1.at(3*i) = samples.at(0).at(3*i);
	fps2.at(3*i) = samples.at(1).at(3*i);
	fps1.at(3*i+1) = samples.at(0).at(3*i+1);
	fps2.at(3*i+1) = samples.at(1).at(3*i+1);
	fps1.at(3*i+2) = samples.at(0).at(3*i+2);
	fps2.at(3*i+2) = samples.at(1).at(3*i+2);
	if (i == position-1+s)
		break;
	
}

	fps1.resize(3*(position+s));
	fps2.resize(3*(position+s));
	first_part.set_alignment_bits(fps1,fps2); 

for (size_t i=position+s;i<samples.at(1).size()/3;++i){
      	sps1.at(3*(i-position-s)) = samples.at(0).at(3*i);
	sps2.at(3*(i-position-s)) = samples.at(1).at(3*i);
	sps1.at(3*(i-position-s)+1) = samples.at(0).at(3*i+1);
	sps2.at(3*(i-position-s)+1) = samples.at(1).at(3*i+1);
	sps1.at(3*(i-position-s)+2) = samples.at(0).at(3*i+2);
	sps2.at(3*(i-position-s)+2) = samples.at(1).at(3*i+2);

}

	sps1.resize(samples.at(1).size()-3*(position+s));
	sps2.resize(samples.at(1).size()-3*(position+s));
	cout << "size " << sps1.size() << endl;

	second_part.set_alignment_bits(sps1,sps2);


}
}


void pw_alignment::base_translate(char base, bool  & bit1, bool & bit2, bool & bit3) {
	switch(base) {
			case 'A':
			case 'a':
				bit1 = false;
				bit2 = false;
				bit3 = false;

			break;
			case 'C':
			case 'c':
				bit1 = true;
				bit2 = false;
				bit3 = false;

			break;
			case 'T':
			case 't':
				bit1 = false;
				bit2 = true;
				bit3 = false;

			break;
			case 'G':
			case 'g':
				bit1 = true;
				bit2 = true;
				bit3 = false;

			break;
			case 'R':
			case 'r':
			case 'Y':
			case 'y':
			case 'M':
			case 'm':
			case 'K':
			case 'k':
			case 'W':
			case 'w':
			case 'S':
			case 's':
			case 'B':
			case 'b':
			case 'D':
			case 'd':
			case 'H':
			case 'h':
			case 'V':
			case 'v':
			case 'N':
			case 'n':
				bit1 = false;
				bit2 = false;
				bit3 = true;

			break;
			case '-':
			case '.':
				bit1 = true;
				bit2 = false;
				bit3 = true;

			break;
			default:
			cerr << "Error: Illegal character in DNA sequence: " << base << endl;
			exit(1);
			break;
		}
}

char pw_alignment::base_translate_back(bool bit1, bool bit2, bool bit3) {

	if(bit1) {
		if(bit2) {
			if(bit3) {
				cerr << "Error: wrong bit vector 111" << endl;
				exit(1);
			} else {
				return 'G';
			}
		
		} else {
			if(bit3) {
				return '-';
			} else {
				return 'C';
			}

		}	
	
	} else {
		if(bit2) {
			if(bit3) {
				cerr << "Error: wrong bit vector 011" << endl;
				exit(1);
			} else {
				return 'T';
			}

		} else {
			if(bit3) {
				return 'N';
			} else {
				return 'A';
			}

		}
	}
}
	vector<bool> pw_alignment::getsample1()const{
	return samples.at(0);
}
	vector<bool> pw_alignment::getsample2()const{
	return samples.at(1);
}
	size_t pw_alignment::getbegin1()const{
	return begins.at(0);
}
	size_t pw_alignment::getbegin2()const{
	return begins.at(1);
}
	size_t pw_alignment::getend1()const{
	return ends.at(0);
}
	size_t pw_alignment::getend2()const{
	return ends.at(1);
}
	size_t pw_alignment::getreference1() const{
	return references.at(0);
}
	size_t pw_alignment::getreference2() const{
	return references.at(1);
}
	vector<bool> pw_alignment::getsample(size_t id)const{
	return samples.at(id);
}
	size_t pw_alignment::getbegin(size_t id)const{
	return begins.at(id);
}
	size_t pw_alignment::getend(size_t id)const{
	return ends.at(id);
}
	size_t pw_alignment::getreference(size_t id)const{
	return references.at(id);
}


	bool compare_pw_alignment::operator()(const pw_alignment *const &a, const pw_alignment *const &b){
	size_t asmaller = 0;
	size_t abigger = 1;
	if(a->getreference(0) > a->getreference(1)) {
		asmaller = 1;
		abigger = 0;
	} else if(a->getreference(0) == a->getreference(1)) {
		if(a->getbegin(0) > a->getbegin(1)) {
			asmaller =1;
			abigger = 0;
		} else if(a->getend(0) > a->getend(1)) {
			asmaller =1;
			abigger = 0;
		}
	}
	size_t bsmaller = 0;
	size_t bbigger = 1;
	if (b->getreference(0) > b->getreference(1)){
		bsmaller = 1;
		bbigger = 0;
} 
	else if (b->getreference(0) == b->getreference(1)){
		if(b->getbegin(0) > b->getbegin(1)) {
			bsmaller =1;
			bbigger = 0;
		} else if(b->getend(0) > b->getend(1)) {
			bsmaller =1;
			bbigger = 0;
		}
	
}
	if (a->getbegin(asmaller) < b->getbegin(bsmaller))return true;
	else if (a->getend(asmaller) < b->getend(bsmaller))return true;
	else if ( a->getbegin(abigger) < b->getbegin(bbigger)) return true;
	else if ( a->getend(abigger) < b->getend(bbigger)) return true;
	else return false;
}


	
