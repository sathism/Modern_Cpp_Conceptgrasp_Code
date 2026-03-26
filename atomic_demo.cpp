#include <iostream>
#include <new>
#include <memory>
#include <atomic>
#include <optional>
#include <thread>
#include <chrono>

/* To add documentation */

template <typename T, std::size_t Capacity>
class LockFreeQueue {
   public :
        inline LockFreeQueue(): head(0), tail(0) {
         }

        bool push(const T &value) {
           std::size_t current_tail_index = tail.load(std::memory_order_relaxed);
           std::size_t next_tail_index = (current_tail_index + 1 ) % Capacity;

           if(next_tail_index == head.load(std::memory_order_acquire))
              return false;

           buffer[current_tail_index] = value;
           tail.store(next_tail_index, std::memory_order_release);
           return true;
        }

        bool pop() {
           std::size_t current_head_index = head.load(std::memory_order_relaxed);

           if(current_head_index == tail.load(std::memory_order_acquire))
               return false;

           auto res = buffer[current_head_index];
           std::cout << res << "\n";

           head.store((current_head_index + 1 ) % Capacity, std::memory_order_release);

           return true;
        }
   private :
       /* Cache line length to avoid false sharing */
       alignas(64) std::atomic<std::size_t> head;
       alignas(64) std::atomic<std::size_t> tail;
       T buffer[Capacity];
};

template <std::size_t S>
void producer_thread(LockFreeQueue<int, S>  &ref) {
    std::cout << std::boolalpha << ref.push(10) << "\n";
    std::cout << std::boolalpha << ref.push(11) << "\n";
}

template <std::size_t S>
void consumer_thread(LockFreeQueue<int, S> &ref) {
    std::cout << std::boolalpha << ref.pop() << "\n";
    std::cout << std::boolalpha << ref.pop() << "\n";
}

int main() {

    LockFreeQueue<int, 10>  q{};

    std::jthread t(producer_thread<10>, std::ref(q));
    std::jthread t1(consumer_thread<10>, std::ref(q));
    std::this_thread::sleep_for(std::chrono::seconds(10));

}
