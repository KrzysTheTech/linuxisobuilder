document.addEventListener('DOMContentLoaded', function() {
    // This function runs only if it finds the 'download-section' on the page.
    const downloadSection = document.getElementById('download-section');
    
    if (downloadSection) {
        const repo = 'KrzysTheTech/linuxisobuilder';
        const apiUrl = `https://api.github.com/repos/${repo}/releases/latest`;

        fetch(apiUrl)
            .then(response => {
                if (!response.ok) {
                    throw new Error('Network response was not ok: ' + response.statusText);
                }
                return response.json();
            })
            .then(data => {
                // Check for existence of properties
                const versionNumberEl = document.getElementById('version-number');
                const releaseDateEl = document.getElementById('release-date');
                const downloadButtonEl = document.getElementById('download-button');

                // Ensure `tag_name` and `published_at` are available
                if (data.tag_name) {
                    versionNumberEl.textContent = data.tag_name;
                } else {
                    versionNumberEl.textContent = 'Version info not available';
                }

                if (data.published_at) {
                    releaseDateEl.textContent = new Date(data.published_at).toLocaleDateString();
                } else {
                    releaseDateEl.textContent = 'Release date info not available';
                }

                // Set default link to main GitHub release page
                downloadButtonEl.href = data.html_url;

                // Try to find a .deb file in the release assets
                const debAsset = data.assets.find(asset => asset.name.endsWith('.deb'));
                
                if (debAsset) {
                    downloadButtonEl.href = debAsset.browser_download_url;
                    downloadButtonEl.textContent = `Download ${debAsset.name}`;
                } else {
                    downloadButtonEl.textContent = 'View on GitHub';
                }
            })
            .catch(error => {
                // Log error for debugging
                console.error('Error fetching latest release:', error);
                
                // Update UI with error information
                const versionNumberEl = document.getElementById('version-number');
                const releaseDateEl = document.getElementById('release-date');
                const downloadButtonEl = document.getElementById('download-button');

                versionNumberEl.textContent = 'Error';
                releaseDateEl.textContent = 'Could not load data.';
                downloadButtonEl.textContent = 'Link Not Available';
            });
    }
});