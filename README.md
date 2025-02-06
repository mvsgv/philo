PHILOSOPHER 
https://github.com/ArnoChansarel/philo/blob/master/docs/thread.jpeg
￼
*Introduction*
- A thread is a single sequence stream within a process. Because threads have some of the properties of processes, they are sometimes called lightweight processes. What are the differences between process and thread? Threads are not independent from each other unlike processes. A thread is a basic unit of execution of any process. A program comprises many processes and all the processes comprise much simpler units known as threads. So, the thread can be referred to as the basic unit of a process or it is the simpler unit that tother makes the CPU utilization.
- CPU - Un processeur (CPU) est un composant matériel qui constitue l'unité centrale de traitement d'un serveur.
We already have commands like pthread_join, pthread_create etc that will execute a function I will send to it. 

We have to define the place where the API can stock our information about the threat (like a structure for example) in threads we gonna use a simple  variable of type ‘pthread_t’ declaration (like in , char etc).  

- API is the acronym for application programming interface a software intermediary that allows two applications to talk to each other. APIs are an accessible way to extract and share data within and across organizations.
  MUTEX
A mutex is a MUTual EXclusion device, and is useful for protecting shared data structures from concurrent modifications, and implementing critical sections and monitors.
- pthread_mutex_init initializes the mutex object pointed to by mutex according to the mutex attributes pthread_join - the wait function for threads
- pthread_mutex_lock locks the given mutex. If the mutex is currently unlocked, it becomes locked and owned by the calling thread, and pthread_mutex_lock returns immediately. If the mutex is already locked by another thread, pthread_mutex_lock suspends the calling thread until the mutex is unlocked. 
- pthread_mutex_unlock unlocks the given mutex   . The mutex is assumed to be locked and owned by the calling thread on entrance to pthread_mutex_unlock.
- pthread_mutex_destroy destroys a mutex object, freeing the resources it might hold. The mutex must be unlocked on entrance. In the LinuxThreads implementation, no resources are associated with mutex objects, thus pthread_mutex_destroy actually does nothing except checking that the mutex is unlocked. 

*Differences between processes and threads*

* Processes work independently in their own memory, ensuring no interference and better security.
* Resources like CPU and memory are allocated effectively to optimize performance.
* Processes can be prioritized to ensure important tasks get the resources they need.
* When there is a lot of computing and input/output (I/O) work, threads help tasks run at the same time, making the app faster.
* Another advantage for having threads is that since they are lighter weight than processes, they are easier (i.e., faster) to create and destroy than processes.
* Many apps need to handle different tasks at the same time. For example, a web browser can load a webpage, play a video, and let you scroll all at once. Threads make this possible by dividing these tasks into smaller parts that can run together.
CONCLUSION - From the above discussion we can conclude that the process is program under execution that takes more time in creation as well as termination whereas threads are component of process that takes less time in creation as well as termination. Process has PCB whereas threads have their own thread PCB along with the PCB of parent process. 

PCB - A Process Control Block (PCB) is a data structure that is used by an Operating System to manage and regulate how processes are carried out. In operating systems, managing the process and scheduling them properly play the most significant role in the efficient usage of memory and other system resources. In the process control block, all the details regarding the process corresponding to it like its current status, its program counter, its memory use, its open files, and details about CPU scheduling are stored.

* RACE CONDITION
A race condition occurs when two or more threads can access shared data and they try to change it at the same time. Because the thread scheduling algorithm can swap between threads at any time, you don't know the order in which the threads will attempt to access the shared data. Therefore, the result of the change in data is dependent on the thread scheduling algorithm, i.e. both threads are "racing" to access/change the data.


Differences between Mutex an Atomic Variable 
<img width="684" alt="Capture d’écran 2025-02-06 à 14 01 46" src="https://github.com/user-attachments/assets/cfbcac77-1eb7-40e6-b803-52bcb5e47b55" />


Use struct if:

    You prefer clarity and explicitly want to include struct in your declarations.
    You don’t mind the extra verbosity.
    When you declare a struct,
        you must always use the keyword struct when referencing it.

Use typedef struct if:

    You want cleaner, shorter, and more modern-looking code.
    You’re working in large projects where you'll reference the struct often.
    Using typedef struct lets you create an alias(a shorthand) for the struct_t.
    This means you can refer to the struct without needing the struct keyword.

