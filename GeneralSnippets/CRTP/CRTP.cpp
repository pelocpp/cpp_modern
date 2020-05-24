// =====================================================================================
// CRTP
// =====================================================================================

#include <iostream>
#include <string>
#include <chrono> 

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

    // Simple C++ program to demonstrate run-time polymorphism
// and CRTP (Curiously recurring template pattern)
    WEITER
#include <chrono> 
#include <iostream> 

    using Clock = std::chrono::high_resolution_clock;

    // constexpr int MaxIterations = 10;
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

    // base class for all image types 
    class Image {
    protected:
        Dimension m_dimension;

    public:
        // c'tor
        Image(int x, int y) : m_dimension{ 200, 200 } {}

        // public interface
        virtual void draw() = 0;
        virtual Dimension GetDimensionInPixels() = 0;
    };

    class TiffImage : public Image {
    public:
        TiffImage() : Image{ 200, 200 } {}

        void draw() override {
            // just for testing
            Dimension d = GetDimensionInPixels();
        }

        Dimension GetDimensionInPixels() override {
            return m_dimension;
        }
    };

    // base class for all image types. The template parameter T
    // is used to know type of derived class pointed by pointer. 
    template <class T>
    class Image2 {
    protected:
        Dimension m_dimension;

    public:
        // c'tor
        Image2(int x, int y) : m_dimension{ 200, 200 } {}

        void draw() {
            // dispatch call to exact type 
            static_cast<T*>(this)->draw();
        }

        Dimension GetDimensionInPixels() {
            // dispatch call to exact type 
            return static_cast<T*>(this)->GetDimensionInPixels();
        }
    };

    class TiffImage2 : public Image2<TiffImage2> {
    public:
        TiffImage2() : Image2{ 200, 200 } {}

        void draw() {
            // just to make sure that this method is invoked 
            // std::cout << "TiffImage2::draw() called" << std::endl;

            // just for testing
            Dimension d = GetDimensionInPixels();
        }

        Dimension GetDimensionInPixels() {
            return m_dimension;
        }
    };

    // driver code that calls virtual function 
    void test_crtp_01()
    {
        Image* pImage = new TiffImage;

        auto start = Clock::now();

        // call draw several times to make sure performance is visible 
        for (int i = 0; i < MaxIterations; ++i) {
            pImage->draw();
        }

        auto end = Clock::now();
        std::cout << "Time taken: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
            << " microseconds" << std::endl;
    }

    // driver code that calls virtual function 
    void test_crtp_02()
    {
        Image2<TiffImage2>* pImage = new TiffImage2;

        auto start = Clock::now();

        // call draw several times to make sure performance is visible 
        for (int i = 0; i < MaxIterations; ++i) {
            pImage->draw();
        }

        auto end = Clock::now();
        std::cout << "Time taken: "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count()
            << " microseconds" << std::endl;
    }

}

// int main_crtp()
int main()
{
    using namespace CRTP;
    test_01_crtp();
    return 1;
}

// =====================================================================================
// End-of-File
// =====================================================================================