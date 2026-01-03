// =====================================================================================
// Exercises_10_CRTP.cpp
// =====================================================================================

module;

#include "../ScopedTimer/ScopedTimer.h"

module modern_cpp_exercises:crtp;

namespace Exercises_CRTP {

    namespace Exercise_01 {

        constexpr long MaxIterations = 10000;
        constexpr bool Verbose = false;
        constexpr int Width = 400;
        constexpr int Height = 400;

        // classical approach: base class for image types
        class Image {
        protected:
            long m_width;
            long m_height;

        public:
            // c'tor
            Image(int width, int height) : m_width{ width }, m_height{ height } {}

        public:
            // public interface
            virtual void draw() = 0;
            virtual void drawPixel(int position) = 0;
            virtual long getNumPixels() = 0;
        };

        class PngImage : public Image {
        private:
            long m_numPixels;
            long m_currPixel;

        public:
            PngImage() : Image{ 0, 0 }, m_currPixel(0) { setNumPixels(); }
            PngImage(int width, int height) : Image{ width, height } { setNumPixels(); }

            virtual void draw() override {
                // just to prevent optimizer to optimize "too much" some sloppy stuff
                m_currPixel = 0;
                int numPixels = getNumPixels();
                int currPosition = getCurrPixel();
                while (currPosition != numPixels) {
                    drawPixel(currPosition);
                    incCurrPixel();
                    currPosition = getCurrPixel();
                }
            }

            virtual void drawPixel(int position) override {
                if (Verbose) {
                    std::cout << "draw pixel at position " << position << std::endl;
                }
            }

            virtual long getNumPixels() override {
                return m_numPixels;
            }

        private:
            // private helper methods
            void setNumPixels() {
                m_numPixels = m_width * m_height;
            }

            long getCurrPixel() {
                return m_currPixel;
            }

            void incCurrPixel() {
                m_currPixel++;
            }
        };

        // driver code for classical polymorphism benchmark
        static void testExercise_01a_classic_benchmark()
        {
            std::cout << "Classical Polymorphism Benchmark: " << std::endl;

            Image* pImage = new PngImage(Width, Height);

            ScopedTimer watch{};

            // call draw several times to make sure performance is visible 
            for (int i = 0; i < MaxIterations; ++i) {
                pImage->draw();
            }

            long pixels = pImage->getNumPixels();
            std::cout << "Pixels: " << pixels << std::endl;
            std::cout << "Done." << std::endl;
        }

        // CRTP approach: base class for all image types.
        // The template parameter T is used to specify the type
        // of a derived class pointed to by a pointer 
        template <class T>
        class ImageCRTP {
        protected:
            long m_width;
            long m_height;

        public:
            // c'tor
            ImageCRTP(int width, int height) : m_width{ width }, m_height{ height } {}

            void draw() {
                static_cast<T*>(this)->draw();  // dispatch call to exact type 
            }

            void drawPixel(int position) {
                return static_cast<T*>(this)->drawPixel(position);
            }

            long getNumPixels() {
                return static_cast<T*>(this)->getNumPixels();
            }
        };

        class PngImageCRTP : public ImageCRTP<PngImageCRTP> {
        private:
            long m_numPixels;
            long m_currPixel;

        public:
            PngImageCRTP() : ImageCRTP{ 1, 1 }, m_currPixel(0) { setNumPixels(); }
            PngImageCRTP(int width, int height) : ImageCRTP{ width, height } { setNumPixels(); }

            void draw() {
                // just to prevent optimizer to optimize "too much" some sloppy stuff
                m_currPixel = 0;
                int numPixels = getNumPixels();
                int currPosition = getCurrPixel();
                while (currPosition != numPixels) {
                    drawPixel(currPosition);
                    incCurrPixel();
                    currPosition = getCurrPixel();
                }
            }

            void drawPixel(int position) {
                if (Verbose) {
                    std::cout << "draw pixel at position " << position << std::endl;
                }
            }

            long getNumPixels() {
                return m_numPixels;
            }

        private:
            // private helper methods
            void setNumPixels() {
                m_numPixels = m_width * m_height;
            }

            long getCurrPixel() {
                return m_currPixel;
            }

            void incCurrPixel() {
                m_currPixel++;
            }
        };

        // driver code for CRTP benchmark
        static void testExercise_01a_crtp_benchmark()
        {
            std::cout << "CRTP Benchmark: " << std::endl;

            ImageCRTP<PngImageCRTP>* pImage = new PngImageCRTP(Width, Height);

            ScopedTimer watch{};

            // call draw several times to make sure performance is visible 
            for (int i = 0; i < MaxIterations; ++i) {
                pImage->draw();
            }

            long pixels = pImage->getNumPixels();
            std::cout << "Pixels: " << pixels << std::endl;
            std::cout << "Done." << std::endl;
        }

        static void testExercise()
        {
            testExercise_01a_classic_benchmark();
            testExercise_01a_crtp_benchmark();
        }
    }
}

void test_exercices_crtp()
{
    using namespace Exercises_CRTP;

    Exercise_01::testExercise();
}

// =====================================================================================
// End-of-File
// =====================================================================================
