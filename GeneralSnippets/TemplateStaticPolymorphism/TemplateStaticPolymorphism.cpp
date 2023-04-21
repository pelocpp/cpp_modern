// =====================================================================================
// TemplateStaticPolymorphism.cpp // Templates Static Polymorphism
// =====================================================================================

module modern_cpp:template_static_polymorphism;

namespace TemplatesStaticPolymorphism {

    class Coord {
    private:
        int m_x;
        int m_y;

    public:
        Coord() : Coord(0, 0) {}
        Coord(int x, int y) : m_x(x), m_y(y) {}

        friend Coord operator- (const Coord& c1, const Coord& c2) {
            return Coord(c1.m_x - c2.m_x, c1.m_y - c2.m_y);
        }
        Coord abs() {
            return Coord(std::abs(m_x), std::abs(m_y));
        }
    };

    namespace ClassicPolymorphism {

        // common abstract base class GeoObj for geometric objects
        class GeoObj {
        public:
            // draw geometric object:
            virtual void draw() const = 0;
            // return center of gravity of geometric object:
            virtual Coord center_of_gravity() const = 0;
            virtual ~GeoObj() = default;
        };

        // concrete geometric object class Circle - derived from GeoObj
        class Circle : public GeoObj {
        public:
            void draw() const override {
                std::cout << "drawing a circle" << std::endl;
            };

            Coord center_of_gravity() const override { return Coord(); };
        };

        // concrete geometric object class Line - derived from GeoObj
        class Line : public GeoObj {
        public:
            void draw() const override {
                std::cout << "drawing a line" << std::endl;
            };

            Coord center_of_gravity() const override { return Coord(); };
        };

        // draw any GeoObj
        void myDraw(const GeoObj& obj)
        {
            obj.draw(); // call draw() according to type of object
        }

        // compute distance of center of gravity between two GeoObjs
        Coord distance(const GeoObj& x1, const GeoObj& x2)
        {
            Coord c = x1.center_of_gravity() - x2.center_of_gravity();
            return c.abs(); // return coordinates as absolute values
        }

        // draw HETEROGENEOUS collection of GeoObjs
        void drawElems(const std::vector<GeoObj*>& elems)
        {
            for (size_t i = 0; i < elems.size(); ++i) {
                elems[i]->draw(); // call draw() according to type of element
            }
        }

        void test_01() {

            Line line;
            Circle c1;
            Circle c2;
            Circle c3;
            Coord  coord;

            myDraw(line);                // myDraw(GeoObj&) => Line::draw()
            myDraw(c1);                  // myDraw(GeoObj&) => Circle::draw()
            coord = distance(c2, c3);    // distance(GeoObj&,GeoObj&)
            coord = distance(line, c1);  // distance(GeoObj&,GeoObj&)
            std::vector<GeoObj*> vec;    // heterogeneous collection
            vec.push_back(&line);        // insert line
            vec.push_back(&c1);          // insert circle
            drawElems(vec);              // draw different kinds of GeoObjs
        }
    }

    namespace StaticPolymorphism {

        // concrete geometric object class Circle - not derived from any class
        class Circle {
        public:
            void draw() const {
                std::cout << "drawing a circle" << std::endl;
            };

            Coord center_of_gravity() const { return Coord(); };
        };

        // concrete geometric object class Line - not derived from any class
        class Line {
        public:
            void draw() const {
                std::cout << "drawing a line" << std::endl;
            };

            Coord center_of_gravity() const { return Coord(); };
        };

        template<typename GeoObj>
        void myDraw(const GeoObj& obj) // GeoObj is template parameter
        {
            obj.draw();
        }

        // compute distance of center of gravity between two GeoObjs
        template<typename GeoObj1, typename GeoObj2>
        Coord distance(const GeoObj1& x1, const GeoObj2& x2) {
            Coord c = x1.center_of_gravity() - x2.center_of_gravity();
            return c.abs();  // return coordinates as absolute values
        }

        // draw HOMOGENEOUS collection of GeoObjs
        template<typename GeoObj>
        void drawElems(const std::vector<GeoObj>& elems) {
            for (size_t i = 0; i < elems.size(); ++i) {
                elems[i].draw();   // call draw() according to type of element
            }
        }

        void test_02() {

            Line line;
            Circle c1;
            Circle c2;
            Circle c3;
            Coord  coord;
            // Note: Type Deduction
            myDraw(line);                   // myDraw<Line>(Line&) => Line::draw()
            myDraw(c1);                     // myDraw<Circle>(Circle&) => Circle::draw()

            coord = distance(c2, c3);       // distance<Circle,Circle>(Circle&,Circle&)
            coord = distance(line, c1);      // distance<Line,Circle>(Line&,Circle&)

            // std::vector<GeoObj*> coll;   // ERROR: no heterogeneous collection possible
            std::vector<Circle> vec;        // OK: homogeneous collection possible
            vec.push_back(c1);              // insert circle
            vec.push_back(c2);              // insert circle
            vec.push_back(c3);              // insert circle
            drawElems(vec);                 // draw all circle
        }
    }
}

void main_templates_static_polymorphism()
{

    using namespace TemplatesStaticPolymorphism::ClassicPolymorphism;
    using namespace TemplatesStaticPolymorphism::StaticPolymorphism;

    test_01();
    test_02();
}

// =====================================================================================
// End-of-File
// =====================================================================================
