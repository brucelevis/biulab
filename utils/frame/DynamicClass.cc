#include "DynamicClass.hh"

extern "C" {
void* createByClassName(const char* strClassName) {
    return DYN_CREATE(strClassName);
}
}

namespace DYN_CLASS {
CFactoryList* CFactoryList::_head = 0;

void* Create(const char* class_name) {
    void*               new_object = 0;
    const CFactoryList* cur        = CFactoryList::_head;

    // printf("11 %s\n", class_name);
    for (; cur; cur = cur->m_next) {
        // printf("hello\n");
        /* if class_name matched, object will then be created and returned */
        if (new_object = cur->m_item->Create(class_name)) {
            // printf("ok %s\n", class_name);
            printf("new:%x \n", new_object);
            break;
        }
    }

    return new_object;
}

/* delete linkage from CFactoryList when some class factory destroyed */
CFactoryList::~CFactoryList(void) {
    CFactoryList** m_nextp = &CFactoryList::_head;

    for (; *m_nextp; m_nextp = &(*m_nextp)->m_next)
        if (*m_nextp == this) {
            *m_nextp = (*m_nextp)->m_next;
            break;
        }
}
} // namespace DYN_CLASS
