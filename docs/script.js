document.addEventListener('DOMContentLoaded', function() {
    // Set the current year in the footer
    const currentYear = new Date().getFullYear();
    const currentYearHomeEl = document.getElementById('current-year-home');
    const currentYearDownloadEl = document.getElementById('current-year-download');

    if (currentYearHomeEl) {
        currentYearHomeEl.textContent = currentYear;
    }
    if (currentYearDownloadEl) {
        currentYearDownloadEl.textContent = currentYear;
    }

    // Check if we are on the download page by looking for the download-section
    if (document.getElementById('download-section')) {
        const repo = 'KrzysTheTech/linuxisobuild'; // Updated repository name
        const apiUrl = `https://api.github.com/repos/${repo}/releases/latest`;

        fetch(apiUrl)
            .then(response => {
                if (!response.ok) {
                    throw new Error('Network response was not ok ' + response.statusText);
                }
                return response.json();
            })
            .then(data => {
                // Get the elements
                const versionNumberEl = document.getElementById('version-number');
                const releaseDateEl = document.getElementById('release-date');
                const downloadButtonEl = document.getElementById('download-button');

                // Update the content
                versionNumberEl.textContent = data.tag_name || 'N/A';
                releaseDateEl.textContent = new Date(data.published_at).toLocaleDateString();
                downloadButtonEl.href = data.html_url;

                // Find the .deb asset to link directly
                const debAsset = data.assets.find(asset => asset.name.endsWith('.deb'));
                if (debAsset) {
                    downloadButtonEl.href = debAsset.browser_download_url;
                    downloadButtonEl.textContent = `Download ${debAsset.name}`;
                } else {
                    // Fallback to the main release page if no .deb is found
                    downloadButtonEl.textContent = 'View on GitHub';
                }
            })
            .catch(error => {
                console.error('Error fetching latest release:', error);
                document.getElementById('version-number').textContent = 'Error';
                document.getElementById('release-date').textContent = 'Could not load data.';
                document.getElementById('download-button').textContent = 'Link Not Available';
            });
    }
});
