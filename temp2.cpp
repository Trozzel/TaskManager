#include <cstdio>
#include <cstring>
#include <stdlib.h>
#include <utility>

struct op1{};
struct op2{};

void print_imp(op1) {
	puts("print1");
}

void print_imp(op2) {
	puts("print2");
}

template<class Op>
void printer() {
	print_imp(Op{});
}

struct Ptr{};
struct Name{};

/******************************************************************************/
template<class T>
struct thing {
	private:
		void disp_impl(Ptr) {
			printf("Printing name: %s\n", name);
		}
		void disp_impl(Name) {
			printf("Printing ptr points to: %p\n", ptr);
		}

	public:
		T* ptr;
		char* name;
		thing(const T* t, const char* n) {
			// Copy to ptr
			ptr = (T*)malloc(sizeof(T));
			memcpy(ptr, t, sizeof(T));

			// Copy name
			name = (char*)malloc(strlen(n) + 1);
			memcpy(name, n, strlen(n));
			name[strlen(name)] = '\0';
		}

		~thing() {
			if(ptr) free(ptr);
			if(name) free(name);
		}

		template<class ValName>
			void disp() {
				disp_impl(ValName{});
			}
};

int main()
{
	int* p;
	p = (int*)malloc(sizeof(int));
	*p = 5;

	thing t(p, "George");
	t.disp<Ptr>();

	t.disp<Name>();

	free(p);
}
