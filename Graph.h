#include <unordered_map>
#include <unordered_set>
#include <vector>

class Graph {
  private:
    std::unordered_map<int, std::unordered_set<int>> edges_;
    size_t graph_size_ = 0;

  public:
    Graph() = default;
    explicit Graph(std::vector<std::pair<int, int>>& edges);
    std::unordered_set<int>& neighbours(int vertex);
    std::unordered_map<int, std::unordered_set<int>>& edges();
    std::vector<int> get_vertices_vector();
    size_t size() const;

  private:
    void add(int first, int second);
};


