#ifndef INC_SINGLETON_STARTER_PACK_H_
#define INC_SINGLETON_STARTER_PACK_H_

// constructor, copy costructor and "=" operator to be put in private
#define SINGLETON(x) x();x(x const&);void operator=(x const&);

#endif /* INC_SINGLETON_STARTER_PACK_H_ */
