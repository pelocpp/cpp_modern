// =====================================================================================
// CRTP
// =====================================================================================

#include <iostream>
#include <string>
#include <chrono> 

/*
 * NOTE: Performance Comparison should be executed in RELEASE MODE !!!
 */

namespace CRTP {

    template <typename Child>
    struct Base
    {
        void interface() {
            static_cast<Child*>(this)->implementation();
        }
    };

    struct Derived : Base<Derived>
    {
        void implementation() {
            std::cout << "Derived implementation" << std::endl;
        }
    };

    void test_01_crtp() {

        Derived d;
        d.interface();  // -> "Derived implementation"
    }

    // simple C++ program to demonstrate run-time polymorphism
    // and CRTP (Curiously Recurring Template Pattern)

    using Clock = std::chrono::high_resolution_clock;
    constexpr int MaxIterations = 10000000;

    // dimension of an image 
    class Dimension {
    private:
        int m_x;
        int m_y;

    public:
        Dimension() = default;

        Dimension(int x, int y) {
            m_x = x;
            m_y = y;
        }
    };

    // classical approach: base class for all image types
    class Image {
    protected:
        Dimension m_dimension;
        long long m_numPixels;

    public:
        // c'tor
        Image(int x, int y) : m_dimension{ 200, 200 }, m_numPixels{ 0 } {}

        // public interface
        virtual void draw() = 0;
        virtual Dimension getDimensionInPixels() = 0;
        virtual void incNumPixels() = 0;
        virtual long long getNumPixels() = 0;
    };

    class TiffImage : public Image {
    public:
        TiffImage() : Image{ 200, 200 } {}

        void draw() override {
            // just to prevent optimizer to optimize "too much"
            Dimension d = getDimensionInPixels();
            incNumPixels();
        }

        Dimension getDimensionInPixels() override {
            return m_dimension;
        }

        void incNumPixels() override {
            m_numPixels++;
        }

        long long getNumPixels() override {
            return m_numPixels;
        }
    };

    // CRTP approach: base class for all image types.
    // The template parameter T is used to specify the type
    // of a derived class pointed to by a pointer 
    template <class T>
    class Image2 {
    protected:
        Dimension m_dimension;
        long long m_numPixels;

    public:
        // c'tor
        Image2(int x, int y) : m_dimension{ 200, 200 }, m_numPixels{ 0 } {}

        void draw() {
            // dispatch call to exact type 
            static_cast<T*>(this)->draw();
        }

        Dimension getDimensionInPixels() {
            return static_cast<T*>(this)->getDimensionInPixels();
        }

        void incNumPixels() {
            static_cast<T*>(this)->incNumPixels();
        }

        long long getNumPixels() {
            return static_cast<T*>(this)->getNumPixels();
        }
    };

    class TiffImage2 : public Image2<TiffImage2> {
    public:
        TiffImage2() : Image2{ 200, 200 } {}

        void draw() {
            // just to prevent optimizer to optimize "too much"
            Dimension d = getDimensionInPixels();
            incNumPixels();
        }

        Dimension getDimensionInPixels() {
            return m_dimension;
        }

        void incNumPixels() {
            m_numPixels++;
        }

        long long getNumPixels() {
            return m_numPixels;
        }
    };

    // driver code that calls virtual function 
    void test_02_crtp()
    {
        Image* pImage = new TiffImage;

        auto start = Clock::now();

        // call draw several times to make sure performance is visible 
        for (int i = 0; i < MaxIterations; ++i) {
            pImage->draw();
        }

        long long pixels = pImage->getNumPixels();
        std::cout << "pixels: " << pixels << std::endl;

        auto end = Clock::now();
        std::cout << "Time taken: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
            << " microseconds" << std::endl;
    }

    // driver code for CRTP benchmark
    void test_03_crtp()
    {
        Image2<TiffImage2>* pImage = new TiffImage2;

        auto start = Clock::now();

        // call draw several times to make sure performance is visible 
        for (int i = 0; i < MaxIterations; ++i) {
            pImage->draw();
        }

        long long pixels = pImage->getNumPixels();
        std::cout << "pixels: " << pixels << std::endl;

        auto end = Clock::now();
        std::cout << "Time taken: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
            << " microseconds" << std::endl;
    }
}

int main_crtp()
{
    using namespace CRTP;
    test_01_crtp();
    test_02_crtp();
    test_03_crtp();

    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================