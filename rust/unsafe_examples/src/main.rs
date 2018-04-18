#![feature(unique, ptr_internals, allocator_api)]

use std::heap;
use std::marker::PhantomData;
use std::mem;
use std::ops::Deref;
use std::ptr::{Unique, self};

pub struct MyVec<T> {
    ptr: Unique<T>,
    cap: usize,
    len: usize,
}

impl<T> MyVec<T> {
    fn new() -> Self {
        assert!(mem::size_of::<T>() != 0, "We're not ready to handle ZSTs");
        MyVec {
            ptr: Unique::empty(),
            len: 0,
            cap: 0,
        }
    }

    fn grow(&mut self) {
        unsafe {
            let align = mem::align_of::<T>();
            let elem_size = mem::size_of::<T>();

            let (new_cap, ptr) = if self.cap == 0 {
                let ptr = heap::allocate(elem_size, align);
                (1, ptr)
            } else {
                let new_cap = self.cap * 2;
                let old_num_bytes = self.cap *elem_size;

                assert!(old_num_bytes <= (::std::isize::MAX as usize) / 2, "capacity overflow");

                let new_num_bytes = old_num_bytes * 2;
                let ptr = heap::reallocate(self.ptr.as_ptr() as *mut _,
                                            old_num_bytes,
                                            new_num_bytes,
                                            align);
                (new_cap, ptr)
            };

            if ptr.is_null() { oom(); }

            self.ptr = Unique::new(ptr as *mut _).unwrap();
            self.cap = new_cap;
        }
    }
}

fn oom() {
    ::std::process::exit(-9999);
}

fn main() {
    let test: MyVec<u32> = MyVec::new();
}
