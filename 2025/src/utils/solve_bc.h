#include <filesystem>
#include <fstream>
#include <memory>

class SolveBaseClass {
  public:
    SolveBaseClass(const SolveBaseClass &) = delete;
    SolveBaseClass(SolveBaseClass &&) = delete;
    SolveBaseClass &operator=(const SolveBaseClass &) = delete;
    SolveBaseClass &operator=(SolveBaseClass &&) = delete;

    explicit SolveBaseClass(const std::filesystem::path &path)
        : input_(std::make_unique<std::ifstream>(path)) {
        if (!input_ && !this->input_->is_open()) {
            std::string err_msg = std::format("could not open file in path: %s", path.c_str());
            throw std::runtime_error(err_msg);
        }
    };
    virtual ~SolveBaseClass() {
        if (this->input_) {
            if (this->input_->is_open()) {
                this->input_->close();
            }
        }
    };

    virtual long solve_part_one() = 0;
    virtual long solve_part_two() = 0;

  protected:
    std::ifstream &input() { return *input_; };

    [[nodiscard("use the returned stream to inspect input")]]
    const std::ifstream &input() const {
        return *input_;
    };

    void reset_file_ptr() {
        if (!this->input_->is_open()) {
            throw std::runtime_error("file not open");
        }
        this->input_->clear();
        this->input_->seekg(0);
    };

  private:
    std::unique_ptr<std::ifstream> input_;
};
