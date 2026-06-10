#include <iostream>
#include <cassert>
#include <filesystem>
#include "models/FileMetadata.h"
#include "repositories/FileRepository.h"

int main() {
    // clean slate — remove old test data if it exists
    std::filesystem::remove("data/metadata.json");

    FileRepository repo;

    // ── test 1: findAll on empty repo returns empty list
    auto all = repo.findAll();
    assert(all.empty());
    std::cout << "findAll empty: PASSED\n";

    // ── test 2: save a file
    FileMetadata meta;
    meta.id           = "a3f9kz2m";
    meta.originalName = "report.pdf";
    meta.storedPath   = "uploads/a3f9kz2m_report.pdf";
    meta.size         = 204800;
    meta.uploadTime   = std::time(nullptr);

    repo.save(meta);
    std::cout << "save: PASSED\n";

    // ── test 3: findById returns the correct record
    FileMetadata found = repo.findById("a3f9kz2m");
    assert(found.id           == meta.id);
    assert(found.originalName == meta.originalName);
    assert(found.size         == meta.size);
    std::cout << "findById: PASSED\n";

    // ── test 4: findAll returns 1 record
    all = repo.findAll();
    assert(all.size() == 1);
    std::cout << "findAll count: PASSED\n";

    // ── test 5: save a second file
    FileMetadata meta2;
    meta2.id           = "b7x2mp4n";
    meta2.originalName = "photo.png";
    meta2.storedPath   = "uploads/b7x2mp4n_photo.png";
    meta2.size         = 512000;
    meta2.uploadTime   = std::time(nullptr);

    repo.save(meta2);
    all = repo.findAll();
    assert(all.size() == 2);
    std::cout << "save second file: PASSED\n";

    // ── test 6: update a record
    meta.size = 999999;
    repo.update(meta);
    FileMetadata updated = repo.findById("a3f9kz2m");
    assert(updated.size == 999999);
    std::cout << "update: PASSED\n";

    // ── test 7: deleteFile removes only one record
    repo.deleteFile("a3f9kz2m");
    all = repo.findAll();
    assert(all.size() == 1);
    assert(all[0].id == "b7x2mp4n");
    std::cout << "deleteFile: PASSED\n";

    // ── test 8: findById throws for deleted ID
    try {
        repo.findById("a3f9kz2m");
        assert(false);  // should never reach here
    } catch (const std::runtime_error&) {
        std::cout << "findById throws on missing ID: PASSED\n";
    }

    // ── test 9: deleteAll leaves empty list
    repo.deleteAll();
    all = repo.findAll();
    assert(all.empty());
    std::cout << "deleteAll: PASSED\n";

    // ── test 10: persistence — create new repo object, data still there
    repo.save(meta2);
    FileRepository repo2;  // fresh object, reads from same file
    all = repo2.findAll();
    assert(all.size() == 1);
    std::cout << "persistence after restart: PASSED\n";

    std::cout << "\nPhase 2 ALL PASSED\n";
    return 0;
}
