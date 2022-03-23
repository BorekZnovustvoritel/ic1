#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <python3.10/Python.h>

char *inputString(size_t *size){
    char *str;
    unsigned base = 32;
    int ch;
    size_t len = 0;
    str = realloc(NULL, sizeof(char)*base);
    if(!str)return str;
    while('\n'!=(ch=fgetc(stdin))){
        str[len++]=ch;
        if(len==base){
            str = realloc(str, sizeof(char)*(base+=16));
            if(!str)return str;
        }
        printf("%c\n", ch);
    }
    printf("Ziju\n");
    str[len++]='\0';
    *size = len;
    printf("Furt ziju\n");
    fflush(stdin);
    return realloc(str, sizeof(char)*len);
}

PyObject *import_name(const char *modname, const char *symbol)
{
    PyObject *u_name, *module;
    u_name = PyUnicode_FromString(modname);
    module = PyImport_Import(u_name);
    Py_DECREF(u_name);

    return PyObject_GetAttrString(module, symbol);
}

short authenticate(char *login, char *password) {
    printf("hi");
    sleep(1);
    PyObject *func = import_name("auth", "auth");
    PyObject *args;
    PyObject *kwargs;
    PyObject *result = 0;
    short ans;

    PyGILState_STATE state = PyGILState_Ensure();
    if (!PyCallable_Check(func)) {
        fprintf(stderr, "Could not call authentization service! Module cannot be run.");
        return -1;
    }
    args = Py_BuildValue("(ss)", login, password);
    kwargs = NULL;
    result = PyObject_Call(func, args, kwargs);
    Py_DECREF(args);
    Py_XDECREF(kwargs);
    if (PyErr_Occurred()) {
        fprintf(stderr, "Could not call authentization service! Module threw an error.");
        PyErr_Print();
        return -1;
    }
    if (!PyBool_Check(result)) {
        fprintf(stderr, "Could not authenticate, module returns wrong data type!");
        return -1;
    }
    ans = PyObject_IsTrue(result);
    return ans;
}

int main() {
    size_t loglen = 0;
    printf("Login as: ");
    char* bufferlog = inputString(&loglen);
    /*printf("login: %s, length: %d", bufferlog, loglen);
    size_t passlen = 0;
    printf("\nPassword: ");
    char* bufferpass = inputString(&passlen);
    printf("\nhuh");
    printf("password: %s, length: %d", bufferpass, passlen);
    printf("\n\n\nNevim");*/
    printf("Authentication value: %d", authenticate("kotek", "piesek"));
    //fflush(stdout);
}
